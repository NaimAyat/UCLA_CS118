# Window-Based Reliable Data Transfer with TCP Tahoe Congestion Control
## 1. Introduction
### 1.1. Design Overview
The objective is to implement a reliable data transfer protocol using UDP sockets in the C programming language. To accomplish this, a simple congestion window-based protocol is developed on top of a selective repeat algorithm. One file, server.c, implements the server side of the transfer. Another file, client.c, represents the client side. The client program acts as a client application – it possesses the ability to request files from the server. 

The client initially sends a message to the server, which includes the name of the requested file. Assuming the requested file is found, the server divides it into multiple packets, each with a maximum length of 1024 bytes. If the file does not exist, the client instead displays a “404: Not Found” error.

The protocol is equipped with four distinct print statements for each step of data transmission: (1) server sends, (2) server receipts, (3) client sends, and (4) client receipts. 

The server prints messages in the following format each time it sends a packet: 

```
“Sending packet” [sequence number] [window size] (“Retransmission”) (“SYN”) (“FIN”)
```

Note that all parenthetical tokens are optional depending on the state of the current data transmission – Retransmission is printed only for retransmitted packets, `SYN` appears when the synchronization flag is enabled, and `FIN` appears when the connection is to be terminated. Bracketed tokens are strictly present in each print.

When the server receives a packet, it prints:

```
“Receiving packet” [ACK number]
```

Conversely, the client relays information on sent packets in the following format:

```
“Sending packet” [ACK number]  (“Retransmission”) (“SYN”) (“FIN”)
```

Upon each receipt of a data packet, the client simply prints:
```
“Receiving packet” [sequence number]
```
### 1.2 Usage
The software package contains the source files `server.c` and `client.c`, as well as both a `README` and `Makefile`. Therefore, the program may be compiled by typing:

```
$ make
```

Once the server and client executables are generated, data transmission may begin. Note that for the following operations, it is assumed that all project files are contained in the same directory.

The server accepts only one argument: a port number. It can be initialized via the command line with the following syntax:

```
$ ./server <port>
```

Meanwhile, the client program accepts three arguments: the server hostname, a port number, and the name of a file to retrieve. It may also be invoked via the command line with by the following statement:

```
$ ./client <hostname> <port> <file>
```

If the wrong number of arguments is provided for either program, the protocol throws an exception and closes the connection.
## 2. Congestion Control
### 2.1. TCP Tahoe
A version of TCP Tahoe is implemented in the transfer protocol to allow for efficient congestion control. First, the initial slow start threshold is set to 15360 bytes. In addition, the initial congestion window size is defined to be 1024 bytes.

During the slow start phase, Tahoe protocol increments the congestion window by one for each acknowledgement that is received. As a result, the congestion window size is effectively doubled for each round-trip time (RTT).

When the congestion window surpasses the slow start threshold, the transfer protocol enters a congestion avoidance phase. Throughout this process, the congestion window is incremented once for each RTT until a data loss is detected.

In general TCP, data loss is measured by a protocol-maintained timer; if an acknowledgement is not received by timeout, a data loss is considered to have occurred. This is largely inefficient, as it introduces an unnecessarily rigid wait duration before each packet loss is addressed. Hence, a fast-retransmit algorithm is implemented to optimize UDP data transfer. When a duplicate acknowledgement is received three consecutive times, packet loss is automatically assumed.

Further, a fast recovery algorithm is implemented in the case of packet loss. After the sender acknowledges a loss, it will reduce the congestion window by a factor of one half. Then, the congestion window is set to either the receiver window size or congestion window size summed with the number of duplicate acknowledgements received – this value assigned is always the lower of the two.
