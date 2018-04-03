#include <stdio.h>
#include <sys/types.h>   // definitions of a number of data types used in socket.h and netinet/in.h
#include <sys/socket.h>  // definitions of structures needed for sockets, e.g. sockaddr
#include <netinet/in.h>  // constants and structures needed for internet domain addresses, e.g. sockaddr_in
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>  /* signal name macros, and the kill() prototype */
#include <sys/wait.h>
#include <sys/stat.h>
#include <math.h>
#include <sys/sendfile.h>

// Typedefs to make things less verbose
#define FALSE 0
#define TRUE !(FALSE)
#define END '\0'

// Error printing function
void error(char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
	int sockfd, newsockfd, portno;

	socklen_t client;

	struct sockaddr_in serv_addr, cli_addr;
	struct stat s;

	// Check user-inputted port number
	if (argc <= 1) {
		error("ERROR: Invalid port number.\n");
	}

	// Initialize socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd <= -1)
		error("ERROR: Failed to create socket.\n");

	// Clear memory
	memset((char *)&serv_addr, 0, sizeof(serv_addr));

	// Initialize address
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) <= -1)
		error("ERROR: Failed to bind address.\n");

	// Listen for a maximum of 5 connections
	listen(sockfd, 5);

	for (;;) {

		// Accept connections
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &client);

		if (newsockfd <= -1)
			error("ERROR: Failed to accept connection.\n");

		// Maxmum length of a GET request for most webservers. Source:
		// https://stackoverflow.com/questions/2659952/maximum-length-of-http-get-request
		char GET[8192];

		// Clear memory
		memset(GET, 0, 8192);

		// Read from client
		int r = read(newsockfd, GET, 8192);
		if (r <= -1)
			error("ERROR: Failed to read from client.\n");
		fprintf(stdout, "%s", GET);

		// Maximum length of a file path in Ubuntu. Source:
		// https://askubuntu.com/questions/859945/what-is-the-maximum-length-of-a-file-path-in-ubuntu
		char fh[4096];
		memset(fh, 0, 4096);
		int fhItr = 0;

		// Support the following file extensions: .html, .htm, .jpeg, .jpg, .gif
		char extension[5];
		memset(extension, 0, 5);
		int extensionItr = 0;

		// Are we dealing with the extension yet?
		int extensionBool = FALSE;

		// Get filehandle and extension
		for (int k = 5; k < 4096; k++) {
			if (GET[k] == ' ') { break; }

			if (GET[k] == '.') { extensionBool = TRUE; }
			else if (extensionBool) {
				extension[extensionItr++] = GET[k];
			}

			// Spaces in path? Note: space represented by "%20"
			if (strncmp(&GET[k], "%20", 3) == 0) {
				fh[fhItr++] = ' ';
				k = k + 2;
			}

			else {
				fh[fhItr++] = GET[k];
			}
		}

		fh[fhItr++] = END;
		extension[extensionItr++] = END;


		// Attempt to open requested file
		FILE* f = fopen(fh, "r");
		if (f == 0) {
			// Return 404 Not Found error
			write(newsockfd, "HTTP/1.1 404 Not Found\n", 14);
			write(newsockfd, "Content-Length: 13\n", 19);
			write(newsockfd, "Content-Type: text/html\n\n", 25);
			write(newsockfd, "<h1>404 Not Found</h1>", 20);
			close(newsockfd);
			continue;
		}

		// Allocate Content-Length for HTML
		stat(fh, &s);
		int size = s.st_size;
		int slen = (ceil(log10(size)) + 21);
		char* str = malloc(slen);
		sprintf(str, "Content-Length: %d\n", size);

		// Send HTTP response
		write(newsockfd, "HTTP/1.1 200 OK\n", 16);
		write(newsockfd, str, slen);

		// Determine extension
		int html = FALSE, jpg = FALSE, gif = FALSE;
		if ((strcasecmp(extension, "html") == 0) || (strcasecmp(extension, "htm") == 0))
			html = TRUE;
		if ((strcasecmp(extension, "jpeg") == 0) || (strcasecmp(extension, "jpg") == 0))
			jpg = TRUE;
		if (strcasecmp(extension, "gif") == 0)
			gif = TRUE;

		// Use proper extension
		if (html)
			write(newsockfd, "Content-Type: text/html\n\n", 25);
		else if (jpg)
			write(newsockfd, "Content-Type: image/jpeg\n\n", 26);
		else if (gif)
			write(newsockfd, "Content-Type: image/gif\n\n", 25);

		// ... or download binary file
		else if (html == FALSE && gif == FALSE && jpg == FALSE || extension[0] == '\0') {
			write(newsockfd, "Content-Type: application/octet-stream\n\n", 40);
			write(newsockfd, "Content-Disposition: attachment\n\n", 33);
		}

		// Max request length
		char buf[8192];
		int fd = fileno(f);

		// Persistent HTTP
		for (;;) {
			int j = read(fd, buf, sizeof buf);
			if (j > 0)
				send(newsockfd, buf, j, 0);
			if (j == 0)
				break;
			if (j <= -1)
				error("ERROR: Failed to send file.\n");
		}
		close(newsockfd);
	}
	close(sockfd);
	return 0;
}