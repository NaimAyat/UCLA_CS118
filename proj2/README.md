# Window-Based Reliable Data Transfer with TCP Tahoe Implementation
## 1. Introduction
### 1.1 Design Overview
The objective is to implement a reliable data transfer protocol using UDP sockets in the C programming language. To accomplish this, a simple congestion window-based protocol is developed on top of a selective repeat algorithm. One file, server.c, implements the server side of the transfer. Another file, client.c, represents the client side. The client program acts as a client application – it possesses the ability to request files from the server. 
The client initially sends a message to the server, which includes the name of the requested file. Assuming the requested file is found, the server divides it into multiple packets, each with a maximum length of 1024 bytes. If the file does not exist, the client instead displays a “404: Not Found” error.
The protocol is equipped with four distinct print statements for each step of data transmission: (1) server sends, (2) server receipts, (3) client sends, and (4) client receipts. 
The server prints messages in the following format each time it sends a packet: 

```
“Sending packet” [sequence number] [window size] (“Retransmission”) (“SYN”) (“FIN”)
```

Note that all parenthetical tokens are optional depending on the state of the current data transmission – Retransmission is printed only for retransmitted packets, `SYN` appears when the synchronization flag is enabled, and `FIN` appears when the connection is to be terminated. Bracketed tokens are strictly present in each print.
When the server receives a packet, it prints:
