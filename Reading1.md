# *Computer Networking: A Top-Down Approach* - Kurose (2016)
## Chapter 1: Computer Networks and the Internet
### 1.1 What is the Internet?
#### 1.1.1 A Nuts-and-Bolts Description
* Devices connected to internet are called *hosts* or *end systems*
* End systems are connected by a network of *communication links* and *packet switches*
* Different links can transmit data at different rates
  * Transmission rate of a link measured in bits/second
* Sending end-system segments data and adds header bytes to each segment; these segments are called *packets*
* Two most prominent types of packet switches are *routers* and *link-layer switches*
  * Forward packets to their ultimate destinations
* End systems access the internet through internet service providers (ISPs)
* End systems, packet switches, and other pieces of the Internet run *protocols* that control the sending and receiving of info
  * Transmission Control Protocol (TCP) and Internet Protocol (IP) are mot important
* Internet standards are developed by Internet Engineering Task Force (IETF)
  * Standards documents are called requests for comments (RFCs)
#### 1.1.2 A Services Description
* Distributed applications involve multiple end systems that exchange data
* Internet apps run on end systems, not in packet switches
* End systems attached to the internet provide an API that specifies how a program running on one end system asks the Internet infrastructure to deliver data to a specific destination program running on another end system
#### 1.1.3 What is a Protocol?
* A protocol defines the format and the order of messages exchanged between two or more communicating entities, as well as the actions taken on the transmission and/or receipt of a message or other event
### 1.2 The Network Edge
* Hosts are divided into two categories: clients and servers
  * Most servers are stored in large data centers
#### 1.2.1 Access Networks
* Two most prevalent types of broadband residential access are digital subscriber line (DSL) and cable
  * DSL provided by telco
  * Cable provided by television company
### 1.3 The Network Core
#### 1.3.1 Packet Switching
* End systems exchange messages with eachother
  * To accomplish this, the source breaks messages into packets
  * Packets travel through links and packet switches
    * Two types of packet switches: routers and link-layer switches
* Most packet switches use *store-and-forward* transmission at the inputs to links
  * Packet switch must receive entire packet before it can begin the transfer the packet onto the outbound link
  * Routers must buffer packet's bits until all are received
  * end-to-end delay (d<sub>end-to-end</sub>) = NL/R
    * N is the number of links in the system
    * R is the transmission rate of each link
    * L is the number of bits transmitted
##### Queuing Delays and Packet Loss
* Each packet switch has multiple links attached; for each attached link, the packet switch has an *output buffer* (AKA output queue) which stores packets that the router is about to send into that link
* If an arriving packet needs to be transmitted but the link is busy with the transmission of another packet, the arriving packet needs to wait in the output buffer
  * This is called *queuing delay*
* Since buffer space is finite, it is possible that an arriving packet finds the buffer full with other packages
  * *Packet loss* occurs in this situation; either the ariving packet or one of the already-queued packets will be dropped
##### Forwarding Tables and Routing Protocols
* Each router has a forwarding table that maps destination addresses to that router's outbound links
#### 1.3.2 Circuit Switching
* There are two approaches to moving data trhough a network: *circuit switching* and *packet switching*
* In circuit-switched networks, the resources needed along a path (buffers, link transmission rate) are reserved for the duration of communcation between the end systems
  * Ex. telephone networks. You establish a *circuit* With the receiver of your call; resources are reserved for the two of you
##### Multiplexing in Circuit-Switched Networks
* A circuit in a link is implemented with either *frequency-division multiplexing (FDM)* or *time-division multiplexing (TDM)*
  * In FDM: the frequency spectrum of a link is divided amongst the connections established across the link
    * A frequency band is dedicated to each connection for the duration of the connection
    * The width of this band is called the bandwidth
  * In TDM: time is divided into frames of fixed duration, each frame is divided into a fixed number of time slots
##### Packet Switching Versus Circuit Switching
* Packet switching not suitable for real-time services (ie. telephone and video conference calls) 
* Packet switching offers better sharing of transmission capacity and is simpler + more efficient to implement
#### 1.3.3 A Network of Networks
* PoP (point of presence): group of one or more routers at the same location in the provider's network where customer ISPs can connect into the provider ISP
### 1.4 Delay, Loss. and Throughput in Packet-Switched Networks
#### 1.4.1 Overview of Delay in Packet-Switched Networks
* Types of delay: nodal processing delay, queuing delay, transmission delay; together, these give a total nodal delay
* d<sub>nodal</sub> = d<sub>proc</sub> + d<sub>queue</sub> + d<sub>trans</sub> + d<sub>prop</sub>
##### Processing Delay
* Time required to examine the packet's header and determine where to direct the packet
##### Queuing Delay
* Time waited in queue before packet transmitted onto link
* Unlike other delays, can vary from packet to packet
* First packet does not experience queuing delay
* Let a denote the average rate at chich packets arrive at the queue (packets/sec)
  * Average rate at which bits arrive in the queue is La bits/sec
  * Assume the queue can hold infinite bits. The ratio La/R is called *traffic intensity*
    * If La/R > 1, the average rate at which bits arrive at the queue exceeds the rate at which bits can be transmitted from the queue. Hence, queuing delay will approach infinity. Hence, systems must never be designed with a traffic intensity greater than 1.
    * If La/R < 1, the nature of arriving traffic impacts queuing delay. If packets arrive simultaneously every (L/R)N seconds, the first packet has no queuing delay the second packet has queuing delay L/R, and the nth packet has queuing delay (n-1)L/R 
##### Transmission Delay
* d<sub>trans</sub> = L/R, where L is the number of bits and R is the transmission rate of the link
##### Propagation Delay
* After a bit is pushed into the link, the time required to propagate from the beginning of the link to router B
  * Distance between two routers divided by the propagation speed: d<sub>prop</sub> = d/s, where d is the distance between router A and router B and s is the propagation speed of the link
#### 1.4.3 End-to-End Delay
* So far, we've focused on nodal delay (delay at single router)
* Now, consider todal delay from source to destination. Suppose there are N-1 routers between source and dest
  * d<sub>end-end</sub> = N(d<sub>proc</sub> + d<sub>trans</sub> + d<sub>prop</sub>)
  * Where d<sub>trans</sub> = L/R; L is packet size
#### 1.4.4 Throughput in Computer Networks
* Instantaneous throughput at any instant of time is the rate in bits/sec at which host B is receiving a file
* Average throughput is F/T where F is the total number of bits in the file and T is the time it took to receive
### 1.5 Protocol Layers and Their Service Models
#### 1.5.1 Layered Architecture
##### Protocol Layering
* Transport-layer and application-layer protocols are almost always implemented in software in the end systems
* Five-layer internet protocol stack:
  1. Application
  2. Transport
  3. Network
  4. Link
  5. Physical
##### Application Layer
* Includes protocols such as HTTP, SMTP, and FTP
* Protocols distrubuted over multiple end system
* App layer packets are *messages*
##### Transport Layer
* Transports app-layer messages between app endpoints. There are two transport protocols:
  * TCP
  * UDP
* TCP provides a connection-oriented service to its applications, guaranteeing delivery of messages and flow control
  * Breaks long messages into shorter segments and provides a congestion-control mechanism, so a source throttles its transmission rate when the network is congested
* UDP provides a connectionless service: no reliability, no flow control, and no congestion control
* Transport Layer packets are *segments*
##### Network Layer
* Moves network-layer packets (*datagrams*) from one host to another
* The transport-layer protocol gives a segment and destination address to the network layer, just as you give the postal service a letter with an address
* The network layer delivers the segment to the transport layer in the destination host
* Includes IP protocol: defines fields in the datagram as well as how end systems and routers act in these fields
##### Link Layer
* Routes a datagram through a series of routers between the source and destination
* At each node, the network layer passes the datagram down to the link layer, which delivers the datagram to the next node along the route. At this next node, the link layer passes the datagram up to the network layer
* Examples of link-layer protocols: Ethernet, Wifi
* Link-layer packets are *frames*
##### Physical Layer
* Moves individual bits within a frame from one node to the next
#### 1.5.2 Encapsulation
* At the sending host, an app-layer message is passed to the transport layer. In the simplest case, the transport layer takes the message and appends additional info that will be used by the receiver-side transport layer
  * The application-layer message and the transport-layer header info together constitute the transport-layer segment
  * The transport layer thus encapsulates the app-layer message, including info allowing the receiver-side transport layer to deliver the message up to the appropriate application and error-detection bits to allow the receiver to determine whether bits in the message have been changed in route
    * The transport layer then passes the segment to the network layer, which adds network-layer header information such as source and destination end system addresses, creating a datagram
      * Network layer passes datagram to link layer, which adds its own lin-layer header info and creates a frame
   * Hence, for each layer, a packet has two types of fields: header fields and a payload field. The payload is typically a packet from the layer above
### 1.4 Networks Under Attack
* Compromised host may be enrolled in a network of similarly compromised devices, known as a *botnet* 
* Malware can sepread in the form of a virus or worm
  * Virus: require some form of user interaction to infect a device (ex. open an email attachment containing a malicious .exe)
  * Worms: enter a decice without explicit user interaction (ex. a user may be running a vulnerable network app to which an attacker can send malware. It is possible that the application may accept the malware and run it, creating a worm on the device. The newly infected device then scans the Internet, searching for other hosts running the same vulnerable network application to send a copy of the worm)
* Denial-of-service (DoS) attacks render a network, host, or other piece of infrastructure unusable. Three categories:
  1. Vulnerability attack: Send messages to a vulnerable application or OS running on a targeted host. If the right sequence of packets is sent to a vulnerable application or OS, the service can stop or the host can crash
  2. Bandwidth flooding: send a deluge of packets to the targeted host to clog the target's access link, preventing legitimate packets from reaching the server
  3. Connection flooding: attacker establishes a large number of half- or fully-open TCP connections at the target host. The host is full of bogus connections, so it stops accepting legitimate connections
* Distributed denial-of-service (DDos): attacker controls multiple sources and each source blasts traffic at target
* Easy to create a packet with an arbitrary source address, packet content, and destination address. This is called *IP spoofing*
  * To combat this, implement *end-point authentication*
## Chapter 2: Application Layer
### 2.1 Principles of Network Applications
* Application architecture is designed by the app developer. There are two choices:
  1. Client-server architecture
     * Always-on host, called the server, services requests from many other hosts, called clients
  2. Peer-to-peer (P2P) architecture
     * Minimal (or no) reliance on dedicated servers; the application exploits direct communication between pairs of intermittently connected hosts called *peers*
#### 2.1.2 Processes Communicating
##### Client and Server Processes
* The process that initiates the communication is the client; the process that waits to be contacted is the server
##### The Interface Between the Process and the Computer Network
* A socket is the interface between the app layer and the transport layer within a host. Also called the API between the application and the network
##### Addressing Processes
* A host is identified by its IP address
* The sending process identifies the receiving process with a port number
#### 2.1.3 Transport Services Available to Applications
##### Reliable Data Transfer
* Not necessary for loss-tolerant applications, such as video conference software
##### Throughput
* Applications that have throughput requirements are said to be bandwidth-sensitive applications. Many current multimedia applications are bandwidth sensitive
* Elastic applications, on the other hand, can make use of as much, or as little, throughput as happens to be available. Electronic mail, file transfer, and Web transfers are all elastic applications
##### Timing
* Can guarantee, for example, that data arrives to a socket within 100msec
##### Security 
* For example, in the sending host, a transport protocol can encrypt all data transmitted by the sending process, and in the receiving host, the transport-layer protocol can decrypt the data before delivering the data to the receiving process
#### 2.1.4 Transport Services Provided by the Internet
##### TCP Services
* Connection-oriented service
  * Client and server exchange transport-layer control information before the application-level messages begin to flow
    * This process is called handshaking
    * Allows client and server to prepare for packets
  * After handshaking, a TCP connection is said to exist between the sockets of the two processes
  * Connection is full-duples; two processes can send messages to each other over the connection at the same time
* Reliable data transfer
  * TCP delivers all data without error and in the proper order
* Congestion control
  * Throttles a sending process when the network is congested between sender and receiver
##### UDP Services
* Lightweight, no-frills
* Connectionless; no handshaking
* Internet telephony applications prefer UDP for its speed, though reliable data transfer is not guaranteed
#### 2.1.5 Application Layer Protocols
* Defines how an application's processes, running on different end systems, pass messages to each other
  * Defines the types of messages exchanged (ex. request messages and response messages)
  * The syntax of various message types (Ex. the fields of the message and how they are delineated)
  * The semantics of the fields
  * Rules for determining when and how a process sends messages and responds to messages
### 2.2 The Web and HTTP
#### 2.2.1 Overview of HTTP
* HyperText Transfer Protocol (HTTP) is the Web's application layer protocol
* Implemented in two programs: a client program and a server program
  * Each execute on different end systems, talk to each other by exchanging HTTP messages
  * HTTP defines the structure of these messages
* Web browsers implement the client side of HTTP, so we can use "client" and "browser" interchangeably in this context
* Web servers implement the server side of HTTP, house Web objects, each addressable by a URL
* When a user requests a Web page, the browser sends HTTP request messages for the objects in the page to the server. The server receives the requests and responds with HTTP response messages that contain objects
* HTTP uses TCP as its underlying transport protocol
* HTTP client first initiates a TCP connection with the server. Once the connection is established, the browser and the server processes access TCP through their socket interfaces
#### 2.2.2 Non-Persistent and Persistent Connections
* App developer must choose
* Non-persistent: each request/response pair is sent over a separate TCP connection
* Persistent: all the requests and their corresponding responses are sent over the same TCP connection
##### HTTP with Non-Persistent Connections
* Assume we try to access `http://www.someSchool.edu/someDepartment/home.index`
  1. HTTP client initiates a TCP connection to the server `www.someSchool.edu` on port 80. There will be a socket at the client and a socket on the server
  2. The HTTP client sends an HTTP request message to the server via its socket. The request message includes the path name `/someDepartment/home.index`
  3. The HTTP server process receives the request message via its socket, retrieves the object `/someDepartment/home.index` from its storage (RAM or disk), encapsulates the object in an HTTP response message, and sends the response message to the client via its socket
  4. The HTTP server process tells TCP to close the TCP connection
  5. The HTTP client receives the response message. The TCP connection terminates. The message indicates that the encapsulated object is an HTML file. The client extracts the file from the response message, examines the HTML file, and finds referenes to other objects on the page (ex. JPEGs or Java applets)
  6. The first four steps are repeated for each referenced object on the page
* **Round-trip time (RTT)** is the time it takes for a small packet tor travel from client to server and then back to the client
##### HTTP with Persistent Connections
* Non-persistent connections have shortcomings:
  * A brand-new connection must be established and maintained for each requested object. For each of these connections, TCP buffers must be allocated and TCP variables must be kept in both the client and server
  * Place a significant burden on the Web server, which may be serving requests from hundreds of clients simultaneously
  * Each object suffers a delivery delay of two RTTs; one to establish the TCP connection and one to request and receive an object
* With persistent connections, the server leaves the TCP connection open after sending a response
* Subsequent requests and responses between the same client and server can be sent over the same connection
* An entire web page can be sent over a single persistent TCP connection
* Multiple web pages residing on the same server can be sent from the server to the same client over a single persistent TCP connection
* Requests for objects can be made back-to-back, without waiting for replies to pending requests (pipelining)
* The default mode of HTTP uses persistent connections with pipelining
#### 2.2.3 HTTP Message Format
##### HTTP Request Message
```
GET /somedir/page.html HTTP/1.1
Host: www.someschool.edu
Connection: close
User-agent: Mozilla/5.0
Accept-language: fr
```
* First line is called the request line; subsequent lines are called header lines
* The request line has three fields
  * The method field (GET, POST, HEAD, PUT, or DELETE)
  * The URL field
  * The HTTP version field
* `Connection: close` means we don't want a persistent connection; close the connection after sending the requested object
* `Accept-language: fr` means we prefer French, but return the default language if not available
##### HTTP Response Message
```
HTTP/1.1 200 OK
Connection: close
Date: Tue, 09 Aug 2011 15:44:04 GMT
Server: Apache/2.2.3 (CentOS)
Last-Modified: Tue, 09 Aug 2011 15:11:03 GMT
Content-Length: 6821
Content-Type: text/html

(data data data data data ...)
```
* Three sections: an initial status line, six header lines, then the entity body
* Entity body is the requested object itself
* Status line has three fields: the protocol version field, a status code, and a corresponding status message
#### 2.2.4 User-Server Interaction: Cookies
* HTP servers are stateless; however, it is often desirable for a website to identify users
* Components of a cookie
  1. A cookie header line in HTTP response message
  2. Cookie header line in HTTP request message
  3. Cookie file kept on the user's end system and manager by the user's browser
  4. A back-end database at the website
* The first time a user visits a site, the user can provide a user identification (possibly his or her name). During the subsequent sessions, the browser passes a cookie header to the server, thereby identifying the user to the server. Cookies can thus be used to create a user session layer on top of stateless HTTP
#### 2.2.5 Web Caching
* A Web cache, also called a proxy server, is a network entity that satisfies HTTP requests on the behalf of an origin Web server
* A user’s browser can be configured so that all of the user’s HTTP requests are first directed to the Web cache
* Suppose a browser requests the object at `http://www.someschool.edu/campus.gif`:
  1. Browser establishes a TCP connection to the Web Cache and sends an HTTP request for the object to the Web cache
  2. The Web cache checks to see if it has a copy of the object stored locally. If it does, the Web cache returns the object within an HTTP response message to the client browser
  3. If the Web cache does not have the object, the Web cache opens a TCP connection to the origin server, that is, to `www.someschool.edu`. The Web cache then sends an HTTP request for the object into the cache-to-server TCP connection. After receiving this request, the origin server sends the object within an HTTP response to the Web cache
  4. When the Web cache receives the object, it stores a copy in its local storage and sends a copy, within an HTTP response message, to the client browser (over the existing TCP connection between the client browser and the Web cache)
* A cache is both a server and a client at the same time. When it receives requests from and sends responses to a browser, it is a server. When it sends requests to and receives responses from an origin server, it is a client
* Typically a Web cache is purchased and installed by an ISP. For example, a university might install a cache on its campus network and configure all of the campus browsers to point to the cache. Or a major residential ISP (such as AOL) might install one or more caches in its network and preconfigure its shipped browsers to point to the installed caches.
#### 2.2.6 The Conditional GET
* HTTP has the conditional GET mechanism that allows a cache to verify its objects are up to date
  * A request message is a so-called conditional GET message if (1) the request message uses the GET method and (2) the request message includes an `If-Modified-Since:` header line
### 2.3 File Transfer: FTP
* The user interacts with FTP through an FTP user agent
  * The user first provides the hostname of the remote host, causing the FTP client process in the local host to establish a TCP connection with the FTP server process in the remote host
  * The user then provides the user identification and password, which are sent over the TCP connection as part of FTP commands
  * Once the server has authorized the user, the user copies one or more files stored in the local file system into the remote file system (or vice versa)
* HTTP and FTP are both file transfer protocols that run on TCP. However, the two application-layer protocols have important differences:
  * FTP uses two parallel TCP connections to transfer a file, a control connection and a data connection
    * Control connection is for sending information such as user identification, password, commands to change remote directory, and commands to "put" and "get" files. 
    * The data connection is used to actually send a file
    * Because FTP uses a separate control connection, FTP is said to send its control information out-of-band
  * HTTP uses only one TCP connection; hence it is said to send its control information in-band
* FTP maintains **state** about the user
  * In particular, the server must associate the control connection with a specific user account, and the server must keep track of the user’s current directory as the user wanders about the remote directory tree
#### 2.4 Electronic Mail in the Internet
* Three major components:
  * User agents
  * Mail servers
  * Simple Mail Transfer Protocol (SMTP)
* Mail servers form the core of the e-mail infrastructure. Each recipient, such as Bob, has a mailbox located in one of the mail servers. Bob’s mailbox manages and maintains the messages that have been sent to him
* A typical message starts its journey in the sender’s user agent, travels to the sender’s mail server, and travels to the recipient’s mail server, where it is deposited in the recipient’s mailbox
#### 2.4.1 SMTP
* Older than HTTP; legacy technology. Restricts body of mail messages to 7-bit ASCII
* Example: Alice sends Bob an ASCII message
  1. Alice invokes her user agent for e-mail, provides Bob’s e-mail address (for example, `bob@someschool.edu`), composes a message, and instructs the user agent to send the message
  2. Alice's user agent sends the message to her mail server, where it is placed in a message queue
  3. The client side of SMTP, running on Alice's mail server, sees the message in the message queue. It opens a TCP connection to an SMTP server, running on Bob's mail server
  4. After some initial SMTP handshaking, the SMTP client sends Alice's message into the TCP connection
  5. At Bob's mail server, the server side of SMTP receives the message. Bob's mail server then places the message in Bob's mailbox
#### 2.4.2 Comparison with HTTP
* SMTP and HTTP are both protocols used to transfer files: HTTP transfers files (also called objects) from a Web server to a Web client (typically a browser); SMTP transfers files (that is, e-mail messages) from one mail server to another mail server
* HTTP and SMTP both use persistent connections
* HTTP is mainly a pull protocol: someone loads information on a Web server and users use HTTP to pull the information from the server at their convenience
* SMTP is primarily a push protocol: the sending mail server pushes the file to the receiving mail server
* SMTP restricts messages to 7-bit ASCII (ex. French characters with accents not supported). HTTP does not impose this restriction
#### 2.4.4 Mail Access Protocols
* How does a recipient obtain messages which are sitting in a server within their ISP?
  * User agent can't use SMPT because obtaining messages is a a pull operation, whereas SMTP is a push operation
  * Hence, user must select a mail access protocol
##### POP3
* The simplest mail access protocol; short and readable
* Begins when the user agent opens a TCP connection to the mail server
* POP3 progresses through three phases
  1. Auhtorization: user agent sends a username and password to authenticate the user
  2. Transition: user agent receives messages and the user agent can mark messages for deletion/remove deletion marks/obtain mail statistics
  3. Update: occurs after the client has issued `quit` command, ending POP3 session. The mail server deletes the messages that were marked for deletion
##### IMAP
* Allows user to create remote folders and assign messages to folders
* IMAP associates each message with a folder; when a message arrives at the server, it is associated with the recipient's inbox folder
* The recipient can move the message into a new, user-created folder, read the message, delete the message, etc.
* Unlike POP3, an IMAP server maintains user state info - for example, the names of folders and which messages are associated with which folders
##### Web-Based E-Mail
* The user agent is a web browser, and the user communicates with its remote mailbox via HTTP
* When a recipient wants to access a message in his mailbox, the message is sent from his mail server to his browser using HTTP rather than POP3 or IMAP
* When a sender wants to send an e-mail, the message is sent from his browser to his mail server over HTTP rather than SMTP
### 2.5 DNS - The Internet's Directory Service
* Hots must have identifiers
  * One way to identify a host is a hostname, such as `yahoo.com` or `google.com`
  * Hosts are also identified by IP addresses
#### 2.5.1 Services Provided by DNS (Domain Name System)
* Primary goal is to translate hostnames to IP addresses
* Distributed database implemented in a hierarchy of DNS servers
* Application-layer protocol that allows hosts to query the distributed database
* DNS is commonly employed by other application-layer protocols - including HTTP, SMTP, and FTP - to translate user-supplied hostnames to IP addresses
* For example to access `naimayat.me`, the user host must first obtain the IP address
  1. The user machine runs the client side of the DNS application
  2. The browser extracts the hostname `naimayat.me` from the URL
  3. The DNS client sends a query containing the hostname to a DNS server
  4. The DNS client receives a reply which includes the IP address for the hostname
  5. Once the browser receives the UP address from the DNS, it can initiate a TCP connection to the HTTP server process 
* DNS also provides other important services in addition to hostname translation:
  * Host aliasing: A host with a complicated hostname can have one or more alias names. For example, a hostname such as `relay1.west-coast.enterprise.com` could have, say, two aliases such as `enterprise.com` and `www.enterprise.com`. In this case, the hostname `relay1.westcoast.enterprise.com` is said to be a canonical hostname. Alias hostnames, when present, are typically more mnemonic than canonical hostnames. DNS can be invoked by an application to obtain the canonical hostname for a supplied alias hostname as well as the IP address of the host
  * Mail server aliasing: For obvious reasons, it is highly desirable that e-mail addresses be mnemonic. For example, if Bob has an account with Hotmail, an e-mail address might be as simple as `bob@hotmail.com`. However, the hostname of the Hotmail mail server is more complicated and much less mnemonic than simply hotmail.com (for example, the canonical hostname might be something like `relay1.west-coast.hotmail.com`). DNS can be invoked by a mail application to obtain the canonical hostname for a supplied alias hostname as well as the IP address of the host.
  * Load distribution: DNS can distribute the load among a website's servers by associating a set of IP addresses with a specific server
#### 2.5.2 Overview of How DNS Works
* There are a large number of DNS servers distributed around the globe
* Problems with a single DNS server
  * A single point of failure: if DNS server crashes, so does the entire internet
  * Traffic volume: the single server would have to handle all the DNS queries for millions of hosts
  * Distant centralized database: a single DNS server cannot be "close to" all the querying clients
  * Maintenence: a single DNS server wuld have to keep records for all internet hosts
##### A Distributed, Hierarchical Database
* To deal with scale, DNS uses many server organized in a hierarchical fashion
  * Mappings are distributed accross three types of servers
    1. Root DNS servers. There are 13 in the world.
    2. Top-level domain (TLD) DNS servers. Responsible for top-level domains such as com, org, net, edu.
    3. Authoritative DNS servers. Every organization with publicly accessible hosts (such as Web servers and mail servers) on the Internet must provide publicly accessible DNS records that map the names of those hosts to IP addresses.
* There is another important type of DNS server called the local DNS server. A local DNS server does not strictly belong to the hierarchy of servers but is nevertheless central to the DNS architecture. Each ISP—such as a university, an academic department, an employee’s company, or a residential ISP—has a local DNS server (also called a default name server). When a host connects to an ISP, the ISP provides the host with the IP addresses of one or more of its local DNS servers
##### DNS Caching
* In a query chain, when a DNS server receives a DNS reply (containing, for example, a mapping from a hostname to an IP address), it can cache the mapping in its local memory
* Since mappings between hostnames and IP address are not permanent, DNS servers discard cached information after a period of time (often set to two days)
#### 2.5.3 DNS Records and Messages
* The DNS servers that together implement the DNS distributed database store resource records (RRs), including RRs that provide hostname-to-IP address mappings
* A resource record is a four-tuple that contains the following fields: `(Name, Value, Type, TTL)`
  * TTL is the time to live; it determines when a resource should be removed from a cache
  * The meaning of name and value tepend on type:
    * If type=A, then name is a hostname and value is the IP address for the hostname
    * If type=NS, then name is a domain and value is the hostname of an authoritative DNS server that knows how to obtain the IP addresses for hosts in the domain
    * If type=CNAME, then Value is a canonical hostname for the alias hostname name. This record can provide querying hosts the canonical name for a hostname
    * If type=MX, then value is the canonical name of a mail server that has an alias hostname name
##### DNS Messages
* First 12 bytes is the header section
  1. 16-bit number that identifies the query
  2. A 1-bit query/reply flag indicates when the message is a query or reply
  3. A1-bit authoritative flag is set in a reply message when a DNS server is an authoritative server for a queried name
  4. A 1-bit recursion-desired flag is set when a client (host or DNS server) desires that the DNS server perform recursion when it doesn't have the record
  5. A 1-bit recursionavailable field is set in a reply if the DNS server supports recursion
  6. there are also four number-of fields. These fields indicate the number of occurrences of the four types of data sections that follow the header
* Question section contains info about the query
  1. Name field that contains the name that is being queried
  2. Type field that indicates the type of question being asked
* Answer section contains the resource records for the name that was originally queried
* Authority section contains records of other authoritative servers
* Additional section contains other helpful records. For example, the answer field in a reply to an MX query contains a resource record providing the canonical hostname of a mail server. The additional section contains a Type A record providing the IP address for the canonical hostname of the mail server
### 2.6 Peer-to-Peer Applications
* So far, everything covered employs client-server architecture
#### 2.6.1 P2P File Distribution
##### Scalability of P2P Architectures
* Distribution time is the time it takes to get a copy of the file to all N peers
* Distribution time for client-server architecture D<sub>cs</sub> ≥ max{NF/u<sub>s</sub>, F/d<sub>min</sub>}
  * Where N = number peers, F = file size in bits, u<sub>s</sub> = server upload rate, d<sub>min</sub> = download rate of the peer with the lowest download rate
* In P2P observe:
  * At the beginning of the distribution, only the server has the file. To get this file into the community of peers, the server must send each bit of the file at least once into its access link. Thus, the minimum distribution time is at least F/u<sub>s</sub>. (Unlike the client-server scheme, a bit sent once by the server may not have to be sent by the server again, as the peers may redistribute the bit among themselves.)
  * As with the client-server architecture, the peer with the lowest download rate cannot obtain all F bits of the file in less than F/d<sub>min</sub> seconds. Thus the minimum distribution time is at least F/d<sub>min</sub>.
  * Finally, observe that the total upload capacity of the system as a whole is equal to the upload rate of the server plus the upload rates of each of the individual peers, that is, u<sub>total</sub> = u<sub>s</sub> + u<sub>1</sub> + ... + u<sub>N</sub>. The system must deliver (upload) F bits to each of the N peers, thus delivering a total of NF bits. This cannot be done at a rate faster than utotal. Thus, the minimum distribution time is also at least NF/(u<sub>s</sub> + u<sub>1</sub> + ... + u<sub>N</sub>).
* **Thus, the minimum distribution time for client-server architectures increases linearlly with the number of peers, wheras P2P is logarithmic**
##### BitTorrent
* Collection of all peers participating in the distribution of a file is called a torrent
* Peers in a torrent download equal-size chunks of the file from one another
* When a peer first joins a torrent, it has no chunks
* When a peer accumulates chunks, it also uploads them to other peers
* Once a peer has aquired the entire file, it may (selfishly) leave the torrent or remain and continue to upload chunks to other peers
* A peer may leave the torrent at any time with only a subset of chunks, and later rejoin the torrent
* Each torrent has an infrastructure node called a tracker
  * When a peer joins a torrent, it registers itself with the tracker and periodically informs the tracker that it is still in the torrent
* When a new peer joins the torrent, the tracker randomly selects a subset of peers from the set of participants and sends their addresses to the new peer. The new peer can then establish concurrent TCP connections with all the peers on this list, called "neighboring peers"
  * As time passes, some of these neighbors may leave and some may attempt to join
* At any given time, each peer will have a subset of chunks from the file
* Periodically, a peer will ask each of its neighbors for the list of the chunks they have. If it has L neighbors, it will obtain L lists of chunks 
  * With this knowledge, the peer uses a techique called *rarest first* to request the rarest chunks for download, aiming to equalize the numbers of copies of each chunk in the torrent
* A peer gives priority to the four neighbors that are supplying data at the highest rates
  * The peer reciprocates and sends chunks to these same four peers. Every 10 seconds, the peer recalculates the rates and possibly modifies the set of four peers
  * These four peers are said to be *unchoked*
  * Every 30 seconds, the peer picks another neighbor at random and sends it chunks. This randomly selected peer is said to be *optimistically unchoked* in hopes that the random peer will start sending data back
    * The optimistically unchoked peer could become one of our top four uploaders, and hence we start trading data
    * This is a tit-for-tat system allowing peers of similar upload capacity to share with each other
## Chapter 3: Transport Layer
### 3.1 Introduction and Transport-Layer Services
* Transport layer protocol provides for logical communication between application processes running on different hosts
* Transport-layer packets are called *segments*
#### 3.1.1 Relationship Between Transport and Network Layers
* A transport-layer protocol provides logical communication between processes running on different hosts, a network-layer protocol provides logical communication between hosts
#### 3.1.2 Overview of the Transport Layer in the Internet
* The internet makes two transport-layer protcols available to the application layer: UDP (User Datagram Protocol) and TCP (Transmission Control Protocol)
  * When designing an application, the developer must specify one of these two protocols
* IP is a *best-effort delivery service*
* The responsibility of UDP and TCP is to extend IP's delivery service between two end systems to a delivery service between two processes running on the end systems
* Extending host-to-host delivery to process-to-process delivery is called *transport layer multiplexing* and *demultiplexing*
* TCP provides reliable data transfer using flow control, sequence numbers, acknowledgments, and timers. Also provides congestion control for the general good of the internet
### 3.2 Multiplexing and Demultiplexing
* Gathering data chunks at the source host from different sockets, encapsulating each data chunk with header information (that will later be used in demultiplexing) to create segments, and passing the segments to the network layer is called **multiplexing**
* Job of delivering data in a transport layer segment to the correct socket is called **demultiplexing**
* Transport layer multiplexing requires
  1. That sockets have unique identifiers
  2. That each segment have special fields that indicate the socket to which the segment is to be delivered
* These special fields are the *source port number field* and the *destination port number field*
  * Each port number is a 16-bit number (range from 0 to 66535)
  * The port numbers ranging from 0 to 1023 are called *well-known port numbers* are restricted, meaning they are reserved for use by well-known application protocols such as HTTP (port 80) and FTP (port 21)
##### Connectionless (UDP) Multiplexing and Demultiplexing
* When a UDP socket is created, the transport layer automatically assigns a port number in the range 1024 to 65535
  * If we use the `bind()` method, we can specify our own address
##### Connection-Oriented (TCP) Multiplexing and Demultiplexing
* A TCP socket is identified by a four-tuple as opposed to UDP's two-tuple: (source IP, source port, destination IP, destination port)
* When a TCP segment arrives from the network to a host, the host uses all four values to direct (demultiplex) the segment to the appropriate socket
### 3.3 Connectionless Transport: UDP
* UDP takes messages from the application process, attaches source and destination port number fields for the multiplexing/demultiplexing service, adds two other small fields, and passes the tesulting segment to the network layer
* The network layer encapsulates the transport layer segment into an IP datagram then makes a best-effort attempt to deliver the segment to the receiving host
* If the segment arrives at the receiving host, UDP uses the destination port number to deliver the segment's data to the correct application process
* Note that there is no handshaking in UDP; it is therefore connectionless
* DNS is an application-layer protocol that typically uses UDP
* When is UDP preferable?
  * We want finer application-level control over what data is sent, and when. Under UDP, as soon as an application process passes data to UDP, UDP will package the data inside a UDP segment and immediately pass the segment to the network layer. TCP, on the other hand, has a congestion-control mechanism that throttles the transport-layer TCP sender when one or more links between the source and destination hosts become excessively congested.
  * We want no connection establishment; since the handshake would introduce delay to establish a connection. This is why DNS uses UDP rather than TCP; it would be much slower otherwise.
  * We want no connection state. A server devoted to a particular app can typically support many more active clients when the application runs over UDP
  * We want smaller packet overhead. TCP headers adds 20 bytes to every segment, while UDP adds only 8
#### 3.3.2 UDP Segment Structure
* UDP has four fields consisting of two bytes each; source port, dest port, length, and checksum
#### 3.3.3 UDP Checksum
* Checksum is used to determine whether bits within a UDP segment have ben alrtered as it is moved from source to destination
* UDP at the sender side performs the 1s complement of the sum of all the 16-bit words in the segment
* Given that neither link-by-link reliability nor in-memory error detection is guaranteed, UDP must provide error detection at the transport layer, on an end-end basis, if the end-end data transfer service is to provide error detection
### 3.4 Principles of Reliable Data Transfer
* TCP is a reliable data transfer protocol that is implemented on top of an unreliable (IP) end-to-end network layer
#### 3.4.1 Building a Reliable Data Transfer Protocol
##### Reliable Data Transfer over a Perfectly Reliable Channel: rdt1.0
* The finite state machine (FSM) definitions for an rdt1.0 sender and receiver state that it is completely reliable
##### Reliable Data Transfer over a Channel with Bit Errors: rdt2.0
* A more realistic model of the underlying channel is one in which bits in a packet may be corrupted
* The message-dictation protocol uses both positive acknowledgements and negative acknowledgements
  * Process of retransmitting data in a reliable data transfer protocol is called *ARQ (Automatic Repeat Request) Protocol*
* Three qualities required of an ARQ protocol to handle bit errors:
  1. Error detection. Set up a checksum: send extra bits from the sender to the receiver to be gathered into the checksum field
  2. Receiver feedback. Since the sender and receiver execute on different end systems (typically), the only way for the sender to learn of the receiver's worldview is for the receiver to provide explicit feedback to the sender. The positive (ACK) and negative (NAK) acknowledgement replies in the message-dictation scenario are examples of such feedback
  3. Retransmission. A packet that is received in error at the receiver will be retransmitted by the sender
* Sender will not send a new piece of data until it is sure that the receiver has received the current packet. Such protocols are called *stop-and-wait* protocols
* We need to add a new field to the data packet and have the sender number its data packets by putting a *sequence number* into this field. The receiver then need only check this sequence number to determine whether or not the received packet is a retransmission
##### Reliable Data Transfer over a Lossy Channel with Bit Errors: rdt3.0
* Suppose now that the underlying channel can lose packets as well as corrupt bits
* How do we detect packet loss, and how do we combat it?
  * If sender waits long enough that it is certain that a packet is lost, it can simply retransmit the packet
    * How long is long enough?
    * The sender must wait at least as long as RTT between the sender and receiver plus whatever time is needed to process a packet at the receiver. Moreover, the protocol should ideally recover from packet loss as soon as possible; waiting for a worst-case delay could mean a long wait until error recovery is initiated
    * The adopted approach, therefore, is for the sender to judiciously choose a wait time such that packet loss is likely (though not guaranteed) to have happened. If an ACK is not received in this time, the packet is retransmitted
    * This introduces the possibility of *duplicate data packets*
    * Implementing a time-based retransmission mechanism requires a countdown timer that can interrupt the sender. The sender will thus need to be able to:
      1. Start the timer each time a packet is sent
      2. Respond to a timer interrupt
      3. Stop the timer
    * Because packet sequence numbers alternate between 0 and 1, protocol rdt3.0 is sometimes known as the *alternating-bit protocol*
#### 3.4.2 Pipelined Reliable Data Transfer Protocols
* Alternating-bit protocol is slow; it is unlikely that anyone would be happy with its performance today
* Rather than operating in a stop-and-wait manner, we should allow the sender to send multiple packets without waiting for ACKs
  * This is called *pipelining*
* Pipelining has the following consequences:
  * The range of sequence numbers must be increased, since each in-transit packet must have a unique sequence number and there may be multiple, in-transit, unacknowledged packets
  * The sender and receiver sides of the protocols may have to buffer more than one packet
  * The range of sequence numbers needed and the buffering requirements will depend on the manner in which a data transfer protocol responds to lost, corrupted, and overly-delayed packets. Two approaches toward pipelined error recovery can be identified: *Go-Back-N* and *selevtive repeat*
