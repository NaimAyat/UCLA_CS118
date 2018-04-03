#include <stdio.h>
#include <netdb.h> 
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <time.h>

unsigned long sysTime() {
	struct timespec x;
	clock_gettime(CLOCK_REALTIME, &x);
	return (x.tv_sec) * 1000 + (x.tv_nsec) / 1000000;
}

int main(int argc, char** argv) {
	struct sockaddr_in srvAddress;
	int srvLength = sizeof(srvAddress);
	int sockfd, sequenceNum = -1, content = -1;
	int SRV = 0, ACK = 0, num = 0, curr = 0;
	struct hostent * server;
	char arr[1024], storArr[30], storage[30][1004];
	FILE *fh;

	if (argc < 4 || argc > 4) {
		printf("ERROR: Wrong number of arguments. Usage: ./client <hostname> <portNumber> <file>\n");
		exit(1);
	}

	char *hostname = argv[1];
	int portNumber = atoi(argv[2]);
	char *fileName = argv[3];

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd <= -1) {
		printf("ERROR: Could not open socket.\n");
		exit(1);
	}

	server = gethostbyname(hostname);
	if (server == NULL) {
		printf("ERROR: Could not find host.\n");
		exit(1);
	}

	bzero((char*)&srvAddress, sizeof(srvAddress));
	srvAddress.sin_family = AF_INET;
	bcopy((char*)server->h_addr, (char*)&srvAddress.sin_addr.s_addr, server->h_length);
	srvAddress.sin_port = htons(portNumber);

	bzero(arr, 1024);
	arr[13] |= (1 << 4);
	unsigned int* ptr = (unsigned int *)(arr + 4);
	*ptr = num;
	strcpy(arr + 20, fileName);

	printf("Sending packet %d SYN\n", num);
	if (sendto(sockfd, arr, 1024, 0, (struct sockaddr *) & srvAddress, srvLength) <= -1) {
		printf("ERROR: Could not send message on socket.\n");
		exit(1);
	}

	int flag = 1, temp;
	for (;;) {
		bzero(arr, 1024);
		temp = recvfrom(sockfd, arr, 1024, MSG_DONTWAIT, (struct sockaddr *) & srvAddress, (socklen_t *)& srvLength);
		if (temp >= 1) {
			unsigned char ctrl = arr[13];
			if (((ctrl >> 4) & 1) == 1) {
				unsigned int* ptr = (unsigned int *)(arr + 4);
				SRV = *ptr;
				printf("Receiving packet %d\n", SRV);

				if ((((ctrl >> 1) & 1) == 1)) {
					unsigned int* ptra = (unsigned int *)(arr + 8);
					ACK = *ptra;
				}

				bzero(arr, 1024);
				arr[13] |= (1 << 1);
				unsigned int* ptrA = (unsigned int *)(arr + 8);
				*ptrA = SRV + 1;
				curr = SRV + 1;
				temp = sendto(sockfd, arr, 1024, 0, (struct sockaddr *) & srvAddress, srvLength);
				printf("Sending packet %d %s\n", curr, "ACK");
			}
			else if (((ctrl >> 5) & 1) == 1) {
				break;
			}
			else {
				if (flag) {
					flag = 0;
					fh = fopen("received.data", "wb");
					int i = 0;
					while (i <= 29) {
						storArr[i] = 0;
						i++;
					}
				}
				unsigned int* ptrb = (unsigned int *)(arr + 4);
				unsigned int sequence = *ptrb;
				printf("Receiving packet %d\n", sequence);
				if (temp <= 1023) {
					sequenceNum = sequence;
					content = temp - 20;
				}
				unsigned int packetNum = sequence / 1024;
				unsigned short* wptr = (unsigned short *)(arr + 14);
				unsigned int win = *wptr;
				if ((sequence >= curr && (sequence - curr) > 0 &&
					(sequence - curr) <= win) ||
					(sequence < curr && (sequence + 30720 - curr) > 0 &&
					(sequence + 30720 - curr) <= win)) {
					memcpy(storage[packetNum], arr + 20, temp - 20);
					storArr[packetNum] = 1;
				}
				else if (sequence == curr) {
					fwrite(arr + 20, sizeof(char), temp - 20, fh);
					curr = (curr + 1024) % 30720;
					while (storArr[curr / 1024]) {
						if (curr == sequenceNum) {
							fwrite(storage[curr / 1024], sizeof(char), content, fh);
						}
						else {
							fwrite(storage[curr / 1024], sizeof(char), 1004, fh);
						}
						storArr[curr / 1024] = 0;
						curr = (curr + 1024) % 30720;
					}
				}
				printf("Sending packet %d\n", curr);
				unsigned int* ptrB = (unsigned int *)(arr + 8);
				*ptrB = curr;
				arr[13] |= (1 << 1);
				temp = sendto(sockfd, arr, 1024, 0, (struct sockaddr *) & srvAddress, srvLength);
				if (temp <= -1) {
					printf("ERROR: Could not send message on socket.\n");
					exit(1);
				}
			}
		}
		unsigned long time = sysTime() + 500;
		if (time <= sysTime() && flag) {
			bzero(arr, 1024);
			arr[13] |= (1 << 4);
			unsigned int* ptrC = (unsigned int *)(arr + 4);
			*ptrC = num;
			strcpy(arr + 20, fileName);
			if (num < 1) {
				printf("ERROR: 404 Not Found.\n");
				exit(1);
			}
			printf("Sending packet %d Retransmission SYN\n", num);
			if (sendto(sockfd, arr, 1024, 0, (struct sockaddr *) & srvAddress, srvLength) <= -1) {
				printf("ERROR: Could not send message on socket.\n");
				exit(1);
			}
			time = sysTime() + 500;
		}
	}
	exit(0);
}