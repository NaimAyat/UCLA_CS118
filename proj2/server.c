#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h> 
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <limits.h>
#include <arpa/inet.h>

struct sockaddr_in cliAddress;
int sockfd, cliLength = sizeof(cliAddress);
char arr[1024];

int WINDOW_SIZE = 1024, lastTrans = -1, 
	finalBytes = -1, SSTHRESH = 15360, 
	duplicateCount = 0, lastSeq = -1, completionFlag = 0;
char storage[30][1004], storArr[30];
unsigned long srvTimeouts[30];
FILE* fh;

// Max of two inputs, for assigning values of SSTHRESH
int max(int x, int y) {
	if (x > y) return x;
	else return y;
}

// Get system time
unsigned long sysTime() {
	struct timespec x;
	clock_gettime(CLOCK_REALTIME, &x);
	return (x.tv_sec) * 1000 + (x.tv_nsec) / 1000000;
}

// Read from file
void readFile(int prev, int curr, FILE* fh) {
	int i = prev;
	while (i != curr) {
		storArr[i / 1024] = 0;
		i = (i + 1024) % 30720;
	}
	i = 0;
	while (i < WINDOW_SIZE) {
		if (feof(fh)) {
			break;
		}
		int seq = (curr + i) % 30720;
		int location = seq / 1024;
		if (storArr[location] == 0) {
			int b = fread(storage[location], 1, 1004, fh);
			if (feof(fh)) {
				lastTrans = seq;
				finalBytes = b;
			}
			storArr[location] = 1;
		}
		i += 1024;
	}
}

// Given sequence num and retransmit flag (indicates whether or not the current
// sequence is a retransmitted packet), send packet.
void sendPacket(int num, int retFlag) {
	int location = num;
	location = location / 1024;
	if (storArr[location] == 0) return;
	char statement[] = " Retransmission";
	if (retFlag == 0) strcpy(statement, "");
	printf("Sending packet %d %d %d%s\n", num, WINDOW_SIZE, SSTHRESH, statement);
	bzero(arr, 1024);
	unsigned int* ptrB = (unsigned int*)(arr + 4);
	*ptrB = num;
	// Note: 14 is window
	unsigned int* ptr = (unsigned int*)(arr + 14);
	*ptr = WINDOW_SIZE / 1024;
	memcpy(arr + 20, storage[location], 1004);
	if ((num != lastTrans) && (sendto(sockfd, arr, 1024, 0, (struct sockaddr*) & cliAddress, cliLength) < 0)) {
		printf("ERROR: Failed to send over socket.");
		exit(1);
	}
	else if (sendto(sockfd, arr, 20 + finalBytes, 0, (struct sockaddr*) & cliAddress, cliLength) < 0) {
		printf("ERROR: Failed to send over socket.");
		exit(1);
	}
}

// Handle timeouts for current sequence
void timeout(int curr) {
	int i = 0;
	while (i < WINDOW_SIZE) {
		int num = (curr + i) % 30720;
		long currentTime = sysTime();
		if (srvTimeouts[num / 1024] < currentTime || srvTimeouts[num / 1024] == ULONG_MAX) {
			int retFlag = srvTimeouts[num / 1024] < currentTime;
			sendPacket(num, retFlag);
			if (retFlag) {
				SSTHRESH = max(WINDOW_SIZE / 2, 2 * 1024);
				WINDOW_SIZE = 1024;
			}
			srvTimeouts[num / 1024] = currentTime + 500;
		}
		i += 1024;
	}
}

// Congestion control Fast Recovery algorithm, given a duplicate sequence and requested file
void fastRecovery(int dupSequence, FILE* fh) {
	WINDOW_SIZE = 3 * 1024 + SSTHRESH;
	int num = dupSequence;
	int srvTime = sysTime() + 500;
	while (num == dupSequence) {
		unsigned char ctrl = arr[13];
		if (recvfrom(sockfd, arr, 1024, MSG_DONTWAIT, (struct sockaddr*) & cliAddress, &cliLength) >= 1 && ((ctrl >> 1) & 1)) {
			int prev = num;
			unsigned int* ptr = (unsigned int*)(arr + 8);
			int num = *ptr;
			WINDOW_SIZE += 1024;
			readFile(prev, num, fh);
		}
		timeout(num);
		if (srvTime < sysTime()) {
			// Retransmit
			printf("Sending packet %d %d %d Retransmission\n", num, WINDOW_SIZE, SSTHRESH);
			bzero(arr, 1024);
			unsigned int* ptrA = (unsigned int*)(arr + 4);
			*ptrA = num;
			unsigned int* ptrB = (unsigned int*)(arr + 14);
			*ptrB = WINDOW_SIZE / 1024;
			memcpy(arr + 20, storage[num / 1024], 1004);
			if ((num < lastTrans || num > lastTrans) && (sendto(sockfd, arr, 1024, 0, (struct sockaddr *) &cliAddress, cliLength) <= -1)) {
				printf("ERROR: Could not send message on socket.\n");
				exit(1);
			}
			else if (sendto(sockfd, arr, 20 + finalBytes, 0, (struct sockaddr*) &cliAddress, cliLength) < 0) {
				printf("ERROR: Could not send message on socket.\n");
				exit(1);
			}
			WINDOW_SIZE = 1024;
			return;
		}
	}
	WINDOW_SIZE = SSTHRESH;
}

int main(int argc, char** argv) {
	// Print wrong number of args message
	if (argc > 2 || argc < 2) {
		printf("ERROR: Wrong number of arguments. Usage: ./server <port_number>\n");
		exit(1);
	}

	// Set port number
	int portNum = atoi(argv[1]);

	// Open UDP socket
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd <= -1) {
		printf("ERROR: Could not open socket.\n");
		exit(1);
	}

	// Pointer to the bufffer in which the value for the requested option is specified
	int optval = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof(int));

	// Get server address
	struct sockaddr_in serveraddr;
	// Zero the byte string
	bzero((char*)& serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons((unsigned short)portNum);

	// Bind server address
	if (bind(sockfd, (struct sockaddr*) & serveraddr, sizeof(serveraddr)) <= -1) {
		printf("ERROR: Server address binding failed.\n");
		exit(1);
	}

	int cumSeq = 0, curr;
	unsigned int randNum = rand() % 30;
	char filename[128];
	int winCounter = 0, winMax, winLow, winHigh;
	for (;;) {
		unsigned char ctrl = arr[13];
		bzero(arr, 1024);
		if ((recvfrom(sockfd, arr, 1024, 0, (struct sockaddr*) & cliAddress, &cliLength) >= 1) && !((ctrl >> 4) & 1)) {
			arr[13] |= (1 << 1);
			// Note: spot 4 is sequence number
			unsigned int* a = (unsigned int *)(arr + 4);
			int temp = *a;
			// Note: spot 8 is ack number
			unsigned int* ptrA = (unsigned int*)(arr + 8);
			*ptrA = temp + 1;
			unsigned int* ptrB = (unsigned int*)(arr + 4);
			*ptrB = randNum;
			printf("Sending packet %d %d %d SYN\n", 4, WINDOW_SIZE, SSTHRESH);
			if (sendto(sockfd, arr, 1024, 0, (struct sockaddr *) & cliAddress, cliLength) <= 0) {
				printf("ERROR: Could not send SYN acknowledgement.\n");
				exit(1);
			}
			strcpy(filename, arr + 20);
		}
		if (recvfrom(sockfd, arr, 1024, 0, (struct sockaddr *) & cliAddress, &cliLength) >= 1) {
			unsigned int* b = (unsigned int*)(arr + 8);
			curr = *b;
			// Print "Receiveing packet" [1 number]
			printf("Receiving packet %d\n", curr);
			if (curr != randNum + 1) {
				printf("ERROR: Failed to receive packet info.\n");
				exit(1);
			}
			break;
		}
	}

	// Open file requested by client.
	fh = fopen(filename, "rb");
	if (fh == NULL) {
		printf("ERROR: Failed to open requested file.\n");
		exit(1);
	}
	int i = 0;
	while (i <= 29) {
		storArr[i] = 0;
		srvTimeouts[i] = ULONG_MAX;
		i += 1;
	}

	readFile(curr, curr, fh);

	while (completionFlag < 1) {
		bzero(arr, 1024);
		if (recvfrom(sockfd, arr, 1024, MSG_DONTWAIT, (struct sockaddr*) & cliAddress, &cliLength) >= 1) {
			unsigned int* c = (unsigned int*)(arr + 4);
			int num = *c;
			srvTimeouts[num / 1024] = ULONG_MAX;
			unsigned int* d = (unsigned int*)(arr + 8);
			int tempSeq = *d;
			// Print "Receiving packet" [ACK]
			printf("Receiving packet %d\n", tempSeq);
			if ((tempSeq >= curr && (tempSeq - curr) > 0 &&
				(tempSeq - curr) <= WINDOW_SIZE) ||
				(tempSeq < curr && (tempSeq + 30720 - curr) > 0 &&
				(tempSeq + 30720 - curr) <= WINDOW_SIZE)) duplicateCount = 0;
			else if (lastSeq == tempSeq) duplicateCount += 1;
			lastSeq = tempSeq;
			// If three duplicate ACKs are received
			if (duplicateCount > 2) {
				// Set SSTHRESH to max(window/2, 2*packet)
				SSTHRESH = max(WINDOW_SIZE / 2, 2 * 1024);
				// Begin Rentransmission
				curr = lastSeq;
				// Print "Retransmission" message
				printf("Sending packet %d %d %d Retransmission\n", curr, WINDOW_SIZE, SSTHRESH);
				bzero(arr, 1024);
				unsigned int* ptrB = (unsigned int*)(arr + 4);
				*ptrB = curr;
				unsigned int* ptr = (unsigned int*)(arr + 14);
				*ptr = WINDOW_SIZE / 1024;
				memcpy(arr + 20, storage[curr / 1024], 1004);
				if ((curr != lastTrans) && (sendto(sockfd, arr, 1024, 0, (struct sockaddr *) &cliAddress, cliLength) < 0)) {
					printf("ERROR: Could not send message on socket.\n");
					exit(1);
				}
				if ((curr == lastTrans) && (sendto(sockfd, arr, 20 + finalBytes, 0, (struct sockaddr *) &cliAddress, cliLength) < 0)) {
					printf("ERROR: Could not send message on socket.\n");
					exit(1);
				}
				// Begin fast recovery
				fastRecovery(curr, fh);
			}
			int prev = curr;
			if ((tempSeq >= curr && (tempSeq - curr) > 0 &&
				(tempSeq - curr) <= WINDOW_SIZE) ||
				(tempSeq < curr && (tempSeq + 30720 - curr) > 0 &&
				(tempSeq + 30720 - curr) <= WINDOW_SIZE)) {
				// If window is smaller than max window size & less than SSTHRESH
				if ((WINDOW_SIZE < (30720 / 2)) && (WINDOW_SIZE < SSTHRESH)) {
					WINDOW_SIZE += 1024;
					winCounter = 0;
				}
				// If window is smaller than max window size & larger than SSTHRESH
				if ((WINDOW_SIZE < (30720 / 2)) && (WINDOW_SIZE >= SSTHRESH)) {
					winLow = (WINDOW_SIZE / 1024) * 1024;
					winHigh = (WINDOW_SIZE / 1024 + 1) * 1024;
					winMax = WINDOW_SIZE / 1024;
					winCounter++;
					WINDOW_SIZE = ((winHigh - winLow) / winMax * winCounter) + winLow;
					if (winCounter == winMax) {
						winCounter = 0;
					}
				}
				curr = tempSeq;
				readFile(prev, curr, fh);

				// Transmission is done
				if (storArr[curr / 1024] == 0) completionFlag += 1;
			}
		}

		// Server timeout
		timeout(curr);
	}

	// Print "FIN" message
	printf("Sending packet %d FIN\n", curr);
	arr[13] |= (1 << 5);

	// Terminate client process
	sendto(sockfd, arr, 1024, 0, (struct sockaddr*) & cliAddress, cliLength);

	// Terminate server process
	fclose(fh);
	exit(0);
}