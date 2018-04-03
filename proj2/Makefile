all: server client

server: server.o 
	gcc -Wall -Wextra -o server server.o
client: client.o 
	gcc -Wall -Wextra -o client client.o
clean:
	rm server client *.o