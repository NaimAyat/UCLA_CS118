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
