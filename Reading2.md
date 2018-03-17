# *Computer Networking: A Top-Down Approach* - Kurose (2016)
## Chapter 4: The Network Layer
### 4.1 Introduction
#### 4.1.1 Forwarding and Routing
* Role of network layer is simple: move packets from sending host to receiving host. We do this via two steps:
  1. Forwarding: When a packet arrives at a router's input link, the router must move it to the appropriate output link.
  2. Routing: The network layer must determine the route packets take as they flow from sender to receiver. This necessitates the use of routing algorithms.
* [Every router has a forwarding table](http://slideplayer.com/5001771/16/images/3/Interplay+between+routing+and+forwarding.jpg)
  * Router forwards packet by examining the value of the field in the arriving packet's header, then using the header value to index into the router's forwarding table
  * The value stored in the forwarding table entry for that header indicates the router's outgoing link interface to which that packet is to be forwarded
  * The header value could be the destination address of the packet or an indication of the connection to which the packet belongs
  * Router receives routing protocol messages, which are used to configure forwarding table
* *Packet switch*: general device that transfers a packet from an input link to an output link, according to the value in a field in the header of the packet
  * Some packet switches, called *link-layer switches*, base their forwarding decision on values in the fields of the link-layer frame
  * Other packet switches, called *routers*, base their forwarding decision on the value in the network-layer field
* Connection setup: routers along the path from source to destination must handshake with each other before packets can flow
#### 4.1.2 Network Service Models
* Some services that could be provided by the network layer:
  * Guaranteed delivery with bounded delay: this service not only guarantees delivery of the packet, but delivery within a specified host-to-host delay bound (for example, within 100 msec).
  * In-order packet delivery
  * Guaranteed minimal bandwidth: network-layer service emulates the behavior of a transmission link of a specified bit rate (for example, 1 Mbps) between sending and receiving hosts
  * Guaranteed maximum jitter: guarantees that the amount of time between the transmission of two successive packets at the sender is equal to the amount of time between their receipt at the destination
  * Security services: encrypt and decrypt datagrams
* Internet network layer provides *best-effort* service: timing between packets is not guaranteed to be preserved, packets are not guaranteed to be received in the order in which they were sent, nor is the eventual delivery of transmitted packets guaranteed
### 4.2 Virtual Circuit and Datagram Networks
#### 4.2.1 Virtual-Circuit Networks
* While the Internet is a datagram network, many alternative network architectures - including those of ATM and frame relay - are virtual-circuit networks and, therefore, use connections at the network layer. These network-layer connections are called virtual circuits (VCs).
* Routers must maintain connection state information
#### 4.2.2 Datagram Networks
* Each time an end system wants to send a packet, it stamps the packet with the address of the destination end system and pops the packet into the network
### 4.3 What's Inside a Router?
* Input ports
  * Perform the physical layer function of terminating an incoming physical link at a router
  * Perform link-layer functions needed to interoperate with the link layer at the other side of the incoming link
* Switching fabric: connects input ports to output ports
* Output ports
  * Stores packets received from switching fabric and transmits them on the outgoing link
  * When a link is bidirectional, the output port is paired with the input port
* Routing processor
  * Executes routing protocols, maintains routing tables and link state info, computes forwarding table
#### 4.3.1 Input Processing
* The lookup performed in the input port is central to the router’s operation—it is here that the router uses the forwarding table to look up the output port to which an arriving packet will be forwarded via the switching fabric
* The forwarding table is computed and updated by the routing processor
#### 4.3.2 Switching
* Switching (forwarding) from an input port to an output port can be accomplished in a number of ways:
  * Switching via memory: The simplest, earliest routers were traditional computers, with switching between input and output ports being done under direct control of the routing processor
  * Switching via bus: an input port transfers a packet directly to the output port over a shared bus, without intervention by the routing processor. This is typically done by having the input port pre-pend a switch-internal label (header) to the packet indicating the local output port to which this packet is being transferred and transmitting the packet onto the bus. Because every packet must cross the single bus, the switching speed of the router is limited to the bus speed
  * Switching via an interconnection network: One way to overcome the bandwidth limitation of a single, shared bus is to use a more sophisticated interconnection network, such as those that have been used in the past to interconnect processors in a multiprocessor computer architecture. A crossbar switch is an interconnection network consisting of 2N buses that connect N input ports to N output ports. When a packet arrives from port A and needs to be forwarded to port Y, the switch controller closes the crosspoint at the intersection of busses A and Y, and port A then sends the packet onto its bus, which is picked up (only) by bus Y. Thus, unlike the previous two switching approaches, crossbar networks are capable of forwarding multiple packets in parallel. However, if two packets from two different input ports are destined to the same output port, then one will have to wait at the input, since only one packet can be sent over any given bus at a time.
#### 4.3.4 Where Does Queueing Occur?
* Clearly, queueing must occur at both input and output ports; when these queues grow, the router memory may be exhausted and cause packet loss
* A consequence of output port queuing is that a packet scheduler at the output port must choose one packet among those queued for transmission
* If there is not enough memory to buffer an incoming packet, a decision must be made to either drop the arriving packet (a policy known as drop-tail) or remove one or more already-queued packets to make room for the newly arrived packet
### 4.4 The Internet Protocol (IP): Forwarding and Addressing in the Internet
#### 4.4.1 Datagram Format
* [IPv4 datagram format (network-layer packet)](https://electronicspost.com/wp-content/uploads/2016/05/4.13.png)
#### 4.4.2 IPv4 Addressing
* IP addresses are typically written in so-called dotted-decimal notation, in which each byte of the address is written in its decimal form and is separated by a period (dot) from other bytes in the address
* Example: in the IP address 193.32.216.9, the 193 is the decimal equivalent of the first 8 bits of the address; the 32 is the decimal equivalent of the second 8 bits of the address, and so on. Thus, the address 193.32.216.9 in binary notation is 11000001 00100000 11011000 0000100
* In IP terms, this network interconnecting three host interfaces and one router interface forms a subnet [RFC 950]. (A subnet is also called an IP network or simply a network in the Internet literature.) IP addressing assigns an address to this subnet: 223.1.1.0/24, where the /24 notation, sometimes known as a subnet mask, indicates that the leftmost 24 bits of the 32-bit quantity define the subnet address. The subnet 223.1.1.0/24 thus consists of the three host interfaces (223.1.1.1, 223.1.1.2, and 223.1.1.3) and one router interface (223.1.1.4). Any additional hosts attached to the 223.1.1.0/24 subnet would be required to have an address of the form 223.1.1.xxx.
* The Internet’s address assignment strategy is known as Classless Interdomain Routing (CIDR—pronounced cider) [RFC 4632]. CIDR generalizes the notion of subnet addressing. As with subnet addressing, the 32-bit IP address is divided into two parts and again has the dotted-decimal form a.b.c.d/x, where x indicates the number of bits in the first part of the address.
* The x most significant bits of an addres of the form a.b.c.d/x constitute the network portion of the IP address, and are often referred to as the prefix (or network prefix) of the address. An organization is typically assigned a block of contiguous addresses, that is, a range of addresses with a common prefix
* The remaining 32-x bits of an address can be thought of as distinguishing among the devices within the organization, all of which have the same network prefix
  * These are the bits that will be considered when forwarding packets at routers within the organization. These lower-order bits may (or may not) have an additional subnetting structure
##### Obtaining a Block of Addresses
* In order to obtain a block of IP addresses for use within an organization’s subnet, a network administrator might first contact its ISP, which would provide addresses from a larger block of addresses that had already been allocated to the ISP
* Is there a global authority that has ultimate responsibility for managing the IP address space and allocating address blocks to ISPs and other organizations? IP addresses are managed under the authority of the Internet Corporation for Assigned Names and Numbers (ICANN)
* The role of the nonprofit ICANN organization [NTIA 1998] is not only to allocate IP addresses, but also to manage the DNS root servers. It also has the very contentious job of assigning domain names and resolving domain name disputes
##### Obtaining a Host Address: the Dynamic Host Configuration Protocol
* Once an organization has obtained a block of addresses, it can assign individual IP addresses to the host and router interfaces in its organization
* Host addresses can also be configured manually, but more often this task is now done using the Dynamic Host Configuration Protocol (DHCP)
* DHCP allows a host to obtain (be allocated) an IP address automatically
* Because of DHCP’s ability to automate the network-related aspects of connecting a host into a network, it is often referred to as a plug-and-play protocol. This capability makes it very attractive to the network administrator who would otherwise have to perform these tasks manually
* For a newly arriving host, the DHCP protocol is a four-step process:
  1. DHCP server discovery: newly arriving host must find a DHCP server with which to interact. This is done using a DHCP discover message, which a client sends within a UDP packet to port 67. the DHCP client creates an IP datagram containing its DHCP discover message along with the broadcast destination IP address of 255.255.255.255 and a "this host" source IP address of 0.0.0.0. The DHCP client passes the IP datagram to the link layer, which then broadcasts this frame to all nodes attached to the subnet
  2. DHCP server offers: DHCP server receiving a DHCP discover message responds to the client with a DHCP offer message that is broadcast to all nodes on the subnet, again using the IP broadcast address of 255.255.255.255. Each server offer message contains the transaction ID of the received discover message, the proposed IP address for the client, the network mask, and an IP address lease time—the amount of time for which the IP address will be valid. It is common for the server to set the lease time to several hours or days
  3. DHCP request: the newly arriving client will choose from among one or more server offers and respond to its selected offer with a DHCP request message, echoing back the configuration parameters.
  4. DHCP ACK: the server responds to the DHCP request message with a DHCP ACK message, confirming the requested parameters
##### Network Address Translation (NAT)
* Simpler approach to IP address allocation for small offices or homes
* NAT-enabled router resides in home
  * The address space 10.0.0.0/8 is one of three portions of the IP address space that is reserved in [RFC 1918] for a private network or a realm with private addresses, such as the home network
    * *A realm with private addresses* refers to a network whose addresses only have meaning to devices within that network.
  * The NAT-enabled router does not look like a router to the outside world. Instead the NAT router behaves to the outside world as a single device with a single IP address
  * For example, all traffic leaving a home has address 138.76.29.7, and all traffic entering the home router must have a destination address of 138.76.29.7. In essence, the NAT-enabled router is hiding the details of the home network from the outside world. Inside the house, however, devices within a given home network can send packets to each other using 10.0.0.0/24 addressing.
* If all datagrams arriving at the NAT router from the WAN have the same destination IP address (specifically, that of the WAN-side interface of the NAT router), then how does the router know the internal host to which it should forward a given datagram? 
   * The trick is to use a NAT translation table at the NAT router, and to include port numbers as well as IP addresses in the table entries
#### 4.4.3 Internet Control Message Protocol (ICMP)
* The network layer of the Internet has three main components
  1. IP protocol
  2. Internet routing protocols
  * ICMP
* ICMP is used by hosts and routers to communicate network- layer information to each other
* ICMP is often considered part of IP but architecturally it lies just above IP, as ICMP messages are carried inside IP datagrams. That is, ICMP messages are carried as IP payload, just as TCP or UDP segments are carried as IP payload
#### 4.4.4 IPv6 
* Successor to IPv4 developed in the 1990s
* [IPv6 datagram](https://electronicspost.com/wp-content/uploads/2016/05/4.24.png)
  * Expanded addressing capabilities: IP address size expanded from 32 to 128 bits
    * New type of address, *anycast address*, allows datagram to be delivered to any one of a group of hosts
  * Streamlined 40-byte header: allows for faster processing of IP datagram
##### Transitioning from IPv4 to IPv6
* Probably the most straightforward way to introduce IPv6-capable nodes is a dual-stack approach, where IPv6 nodes also have a complete IPv4 implementation. Such a node, referred to as an IPv6/IPv4 node in RFC 4213, has the ability to send and receive both IPv4 and IPv6 datagrams
* Alternative to dual-stack: tunneling. With tunneling, the IPv6 node on the sending side of the tunnel (for example, B) takes the entire IPv6 datagram and puts it in the data (payload) field of an IPv4 datagram.
### 4.5 Routing Algorithms
* Typically a host is attached directly to one router, the *default router* for the host (also called the *first-hop* router for the host). Whenever a host sends a packet, the packet is transferred to its default router. 
* We refer to the default router of the source host as the *source router* and the default router of the destination host as the *destination router*
* Global routing algorithm: computes the least-cost path between a source and destination using complete, global knowledge about the network. That is, the algorithm takes the connectivity between all nodes and all link costs as inputs. This then requires that the algorithm somehow obtain this information before actually performing the calculation. The key distinguishing feature here, however, is that a global algorithm has complete information about connectivity and link costs. In practice, algorithms with global state information are often referred to as *link-state (LS)* algorithms, since the algorithm must be aware of the cost of each link in the network.
* Decentralized routing algorithm: calculation of the least-cost path is carried out in an iterative, distributed manner. No node has complete information about the costs of all network links. Instead, each node begins with only the knowledge of the costs of its own directly attached links. Then, through an iterative process of calculation and exchange of information with its neighboring nodes (that is, nodes that are at the other end of links to which it itself is attached), a node gradually calculates the least-cost path to a destination or set of destinations.
* In static routing algorithms, routes change very slowly over time, often as a result of human intervention (for example, a human manually editing a router’s forwarding table).
* Dynamic routing algorithms change the routing paths as the network traffic loads or topology change. A dynamic algorithm can be run either periodically or in direct response to topology or link cost changes. While dynamic algorithms are more responsive to network changes, they are also more susceptible to problems such as routing loops and oscillation in routes.
* In a load-sensitive algorithm, link costs vary dynamically to reflect the current level of congestion in the underlying link. If a high cost is associated with a link that is currently congested, a routing algorithm will tend to choose routes around such a congested link.
#### 4.5.1 The Link-State (LS) Routing Algorithm
* Essentially just [Dijkstra’s algorithm](https://courses.cs.washington.edu/courses/cse326/00wi/handouts/lecture22/img014.gif)
#### 4.5.2 The Distance-Vector (DV) Routing Algorithm
* The distance vector (DV) algorithm is iterative, asynchronous, and distributed. It is distributed in that each node receives some information from one or more of its directly attached neighbors, performs a calculation, and then distributes the results of its calculation back to its neighbors. It is iterative in that this process continues on until no more information is exchanged between neighbors
* [Example](https://www.youtube.com/watch?v=x9WIQbaVPzY)
#### 4.5.3 Hierarchical Routing
* Previously, we simplified routing algorithms to assume that routers were indistinguishable. In practice, this is not efficient because:
  * Scale. As the number of routers increases, the overhead involved in computing, storing, and communicating routing info becomes prohibitive
  * Administrative autonomy. Organizations may run its routers on any algorithm they choose
* These issues can be solved by organizing routers into autonomous systems
* Intraautonomous system routing protocol: routing algorithm running within an autonomous system
### 4.6 Routing in the Internet
#### 4.6.1 Intra-AS Routing in the Internet: RIP
* Intra-AS routing protocols are also known as interior gateway protocols. Historically, two routing protocols have been used extensively for routing within an autonomous system in the Internet: the Routing Information Protocol (RIP) and Open Shortest Path First (OSPF).
* Each link has a cost of 1
* RIP uses the term hop, which is the number of subnets traversed along the shortest path from source router to destination subnet, including the destination subnet
* In RIP, routing updates are exchanged between neighbors approximately every 30 seconds using a RIP response message. The response message sent by a router or host contains a list of up to 25 destination subnets within the AS, as well as the sender’s distance to each of those subnets
* Each router maintains a RIP table known as a routing table
#### 4.6.2 Intra-AS Routing in the Internet: OSPF
* OSPF was conceived as the successor to RIP and as such has a number of advanced features
* At its heart, however, OSPF is a link-state protocol that uses flooding of link-state information and a Dijkstra least-cost path algorithm. 
* A router constructs a complete topological map (that is, a graph) of the entire autonomous system. The router then locally runs Dijkstra’s shortest-path algorithm to determine a shortest-path tree to all subnets, with itself as the root node. Individual link costs are configured by the network administrator
  * The administrator might choose to set all link costs to 1, thus achieving minimum-hop routing, or might choose to set the link weights to be inversely proportional to link capacity in order to discourage traffic from using low-bandwidth links
#### 4.6.3 Inter-AS Routing: BGP
* Border Gateway Protocol version 4  is the de facto standard inter-AS routing protocol in today’s Internet
* Provides each AS a means to
  * Obtain subnet reachability information from neighboring ASs.
  * Propagate the reachability information to all routers internal to the AS.
  * Determine “good” routes to subnets based on the reachability information and on AS policy.
* In BGP, pairs of routers exchange routing information over semipermanent TCP connections using port 179
* The two routers at the end of the connection are called BGP peers, and the TCP connection along with all the BGP messages sent over the connection is called a BGP session
* BGP session that spans two ASs is called an external BGP (eBGP) session
* BGP session between routers in the same AS is called an internal BGP (iBGP) session
* In BGP, destinations are not hosts but instead are CIDRized prefixes, with each prefix representing a subnet or a collection of subnets
* In BGP, an autonomous system is identified by its globally unique autonomous system number (ASN)
* When a router advertises a prefix across a BGP session, it includes with the prefix a number of BGP attributes
##### BGP Route Selection
* BGP uses eBGP and iBGP to distribute routes to all the routers within ASs. From this distribution, a router may learn about more than one route to any one prefix, in which case the router must select one of the possible routes. The input into this route selection process is the set of all routes that have been learned and accepted by the router. If there are two or more routes to the same prefix, then BGP sequentially invokes the following elimination rules until one route remains:
  * Routes are assigned a local preference value as one of their attributes. The local preference of a route could have been set by the router or could have been learned by another router in the same AS. This is a policy decision that is left up to the AS’s network administrator
  * From the remaining routes, the route with the shortest AS-PATH is selected. If this rule were the only rule for route selection, then BGP would be using a DV algorithm for path determination, where the distance metric uses the number of AS hops rather than the number of router hops.
  * From the remaining routes (all with the same local preference value and the same AS-PATH length), the route with the closest NEXT-HOP router is selected. Here, closest means the router for which the cost of the least-cost path, determined by the intra-AS algorithm, is the smallest. This process is called hot-potato routing.
  * If more than one route still remains, the router uses BGP identifiers to select the route
### 4.7 Broadcast and Multicast Routing
* In broadcast routing, the network layer provides a service of delivering a packet sent from a source node to all other nodes in the network
* Multicast routing enables a single source node to send a copy of a packet to a subset of the other network nodes
#### 4.7.1 Broadcast Routing Algorithms
* Perhaps the most straightforward way to accomplish broadcast communication is for the sending node to send a separate copy of the packet to each destination
* Given N destination nodes, the source node simply makes N copies of the packet, addresses each copy to a different destination, and then transmits the N copies to the N destinations using unicast routing
* This N-way unicast approach to broadcasting is simple—no new network-layer routing protocol, packet-duplication, or forwarding functionality is needed
  * Drawbacks: 
    * Inefficient; if the source node is connected to the rest of the network via a single link, then N separate copies of the (same) packet will traverse this single link
    * An implicit assumption of N-way-unicast is that broadcast recipients, and their addresses, are known to the sender. But how is this information obtained? Most likely, additional protocol mechanisms (such as a broadcast membership or destination-registration protocol) would be required.
##### Uncontrolled Flooding
* The most obvious technique for achieving broadcast is a flooding approach in which the source node sends a copy of the packet to all of its neighbors. When a node receives broadcast packet, it duplicates the packet and forwards it to all of its neighbors
  * Problem: if the graph has cycles, then one or more copies of each broadcast packet will cycle indefinitely
  * Even larger problem: When a node is connected to more than two other nodes, it will create and forward multiple copies of the broadcast packet, each of which will create multiple copies of itself (at other nodes with more than two neighbors), and so on. This broadcast storm, resulting from the endless multiplication of broadcast packets, would eventually result in so many broadcast packets being created that the network would be rendered useless
##### Controlled Flooding
* Need to judiciously choose when to flood a packet
  * In sequence-number-controlled flooding, a source node puts its address (or other unique identifier) as well as a broadcast sequence number into a broadcast packet, then sends the packet to all of its neighbors
  * Reverse path forwarding, also sometimes referred to as reverse path broadcast (RPB). The idea behind RPF is simple, yet elegant. When a router receives a broadcast packet with a given source address, it transmits the packet on all of its outgoing links (except the one on which it was received) only if the packet arrived on the link that is on its own shortest unicast path back to the source. Otherwise, the router simply discards the incoming packet without forwarding it on any of its outgoing links
## Chapter 5: The Link Layer: Links, Access, Networks, and LANs
### 5.1 Introduction to the Link Layer
* Any device that runs a link-layer protocol is called a *node*
  * Nodes include hosts, routers, switches, and WiFi access points
  * Communication channels that connect adjacent nodes are *links*
* *Link-layer frames* are link-layer data chunks
* Analogy:
  * Tourist = datagram
  * Transportation segment = link
  * Transportation mode = link-layer protocol
  * Travel agent = routing protocol
#### 5.1.1 The Services Provided by the Link Layer
* Framing: link-layer protocols encapsulate each network-layer datagram within a link-layer frame before transmission over the link
  * Frames consist of a data field (where the network-layer datagram is stored) and a number of header fields
* Link access: a medium access control (MAC) protocol specifies the rules by which a frame is transmitted onto the link.
* Reliable delivery: guarantees to move each network-layer datagram across the link without error
  * A link-layer reliable delivery service is often used for links that are prone to high error rates, such as a wireless link, with the goal of correcting an error locally, on the link where the error occurs, rather than forcing an end-to-end retransmission of the data by a transport- or application-layer protocol.
  * Link-layer reliable delivery is typically unnecessary for low bit-error links, including fiber, coax, and twisted-air copper
* Error detection and correction: The link-layer hardware in a receiving node can incorrectly decide that a bit in a frame is zero when it was transmitted as a one, and vice versa. Such bit errors are introduced by signal attenuation and electromagnetic noise. Because there is no need to forward a datagram that has an error, many link-layer protocols provide a mechanism to detect such bit errors. This is done by having the transmitting node include error-detection bits in the frame, and having the receiving node perform an error check.
#### 5.1.2 Where is the Link Layer Implemented?
* For the most part, the link layer is implemented in a network adapter, also sometimes known as a network interface card (NIC)
  * At the heart of the network adapter is the link-layer controller, usually a single, special-purpose chip that implements many of the link-layer services (framing, link access, error detection, etc.)
  * Thus, much of a link-layer controller’s functionality is implemented in hardware
### 5.2 Error-Detection and Correction Techniques
* Even with the use of error-detection bits there still may be undetected bit errors
#### 5.2.1 Parity Checks
* Employ a single *parity bit*
* The sender includes one extra bit and chooses its value such that the total number of 1s in the original data plus the parity bit is even
  * The receiver counts the number of 1s in the received data; if an odd number is found, the receiver knows a bit error has occured
  * Note that if there is a multiple of 2 total errors, they will go undetected. However, it is rare for bit errors to occur, so this is quite unlikely
* Employ a *two-dimensional parity scheme*: data bits are divided into `i` rows and `j` columns. A parity value is computed for each row and column. The resulting `i + j + 1` parity bits comprise the lin-laer frame's error detection bits
  * Now, the parity of both the column and the row containing the flipped bit will be in error
    * Thus, the receiver will know the exact bit that is in error
#### 5.2.2 Checksumming Methods
* In checksumming techniques, the d bits of data in Figure 5.4 are treated as a sequence of k-bit integers. One simple checksumming method is to simply sum these k-bit integers and use the resulting sum as the error-detection bits. 
  * The Internet checksum is based on this approach—bytes of data are treated as 16-bit integers and summed. The 1s complement of this sum then forms the Internet checksum that is carried in the segment header
#### 5.2.3 Cyclic Redundancy Check (CRC)
* An error-detection technique used widely in today’s computer networks is based on cyclic redundancy check (CRC) codes
* CRC codes operate as follows. Consider the d-bit piece of data, D, that the sending node wants to send to the receiving node. The sender and receiver must first agree on an r + 1 bit pattern, known as a generator, which we will denote as G. We will require that the most significant (leftmost) bit of G be a 1. For a given piece of data, D, the sender will choose r additional bits, R, and append them to D such that the resulting d + r bit pattern (interpreted as a binary number) is exactly divisible by G (i.e., has no remainder) using modulo-2 arithmetic. The process of error checking with CRCs is thus simple: The receiver divides the d + r received bits by G. If the remainder is nonzero, the receiver knows that an error has occurred; otherwise the data is accepted as being correct.
### 5.3 Multiple Access Links and Protocols
* There are two types of network links:
  * A *point-to-point link* consists of a single sender at one end of the link and a single receiver at the other end of the link
  * A *broadcast link*, can have multiple sending and receiving nodes all connected to the same, single, shared broadcast channel
* *Multiple access problem*: how to coordinate the access of multiple sending and receiving nodes to a shared broadcast channel
* *Multiple access protocols*: rules by which nodes regulate their transmission into the shared broadcast channel
* Because all nodes are capable of transmitting frames, more than two nodes can transmit frames at the same time
  * When this happens, all of the nodes receive multiple frames at the same time; that is, the transmitted frames collide at all of the receivers. Typically, when there is a collision, none of the receiving nodes can make any sense of any of the frames that were transmitted. Hence, frames are lost in collisions
* Any multiple access protocol as belonging to one of three categories: *channel partitioning protocols*, *random access protocols*, and *taking-turns protocols*
#### 5.3.1 Channel Partitioning Protocols
* Time-division multiplexing (TDM) and frequency-division multiplexing (FDM) are two techniques that can be used to partition a broadcast channel’s bandwidth among all nodes sharing that channel
  * TDM divides time into time frames and further divides each time frame into N time slots. Each time slot is then assigned to one of the N nodes. Whenever a node has a packet to send, it transmits the packet’s bits during its assigned time slot in the revolving TDM frame. Typically, slot sizes are chosen so that a single packet can be transmitted during a slot time
    * TDM is appealing because it eliminates collisions and is perfectly fair: Each node gets a dedicated transmission rate of R/N bps during each frame time. However, it has two major drawbacks: 
      1. A node is limited to an average rate of R/N bps even when it is the only node with packets to send
      2. a node must always wait for its turn in the transmission sequence—again, even when it is the only node with a frame to send
* While TDM shares the broadcast channel in time, FDM divides the R bps channel into different frequencies (each with a bandwidth of R/N) and assigns each frequency to one of the N nodes
  * FDM thus creates N smaller channels of R/N bps out of the single, larger R bps channel. FDM shares both the advantages and drawbacks of TDM:
    1. Avoids collisions and divides the bandwidth fairly among the N nodes.
    2. A node is limited to a bandwidth of R/N, even when it is the only node with packets to send
* A third channel partitioning protocol is code division multiple access (CDMA)
  * While TDM and FDM assign time slots and frequencies, respectively, to the nodes, CDMA assigns a different code to each node
    * Each node then uses its unique code to encode the data bits it sends. If the codes are chosen carefully, CDMA networks have the wonderful property that different nodes can transmit simultaneously and yet have their respective receivers correctly receive a sender's encoded data bits (assuming the receiver knows the sender’s code) in spite of interfering transmissions by other nodes
#### 5.3.2 Random Access Protocols
##### Slotted ALOHA
* All frames consist of exactly L bits
* Time is divided into slots of L/R seconds (where R is transmission rate in bps)
* Nodes start to transmit frames only at the beginnings of slots
* Nodes are synchronized so that each node knows when the slots begin
* If two or more frames collide in a slot, then all the nodes detect the collision event before the slot ends
Let p be a probability, that is, a number between 0 and 1. The operation of slotted ALOHA in each node is simple:
* When the node has a fresh frame to send, it waits until the beginning of the next slot and transmits the entire frame in the slot
* If there isn’t a collision, the node has successfully transmitted its frame and thus need not consider retransmitting the frame. (The node can prepare a new frame for transmission, if it has one.)
* If there is a collision, the node detects the collision before the end of the slot. The node retransmits its frame in each subsequent slot with probability p until the frame is transmitted without a collision.
* Pros: 
  * Unlike channel partitioning, slotted ALOHA allows a node to transmit continuously at the full rate, R, when that node is the only active node. (A node is said to be active if it has frames to send.) 
  * Slotted ALOHA is also highly decentralizedd because each node detects collisions and independently decides when to retransmit
* Cons:
  * When there are multiple active nodes, two concerns:
    1. A fraction of the slots will have collisions and therefore be wasted
    2. A second fraction will be empty because all active nodes refrain from transmitting as a result of the probabilistic transmission policy
* A slot in which exactly one node transmits is said to be a *successful slot*
* The *efficiency* of a slotted multiple access protocol is defined to be the long-run fraction of successful slots in the case when there are a large number of active nodes, each always having a large number of frames to send
* When there are N actice nodes, the efficiency of slotted ALOHA is Np(1-p)<sup>N-1</sup>
##### ALOHA
* When a frame first arrives, the node immediately transmits it to the broadcast channel
* If a transmitted frame experiences a collision, the node will immediately retransmit the frame with probability p
  * Otherwise, the node waits for a frame transmission time
    * After the wait, the node transmits the frame with probability p, or waits (remaining idle) for another frame time with probability 1 – p
* Efficiency = 1/(2e) = Half that of Slotted ALOHA. this is the price to be paid for a fully decentralized ALOHA protocol
##### Carrier Sense Multiple Access (CSMA)
* *Carrier sensing*: a node listens to the channel before transmitting. If a frame from another node is currently being transmitted into the channel, a node then waits until it detects no transmissions for a short amount of time and then begins transmission
* *Collision detection*: a transmitting node listens to the channel while it is transmitting. If it detects that another node is transmitting an interfering frame, it stops transmitting and waits a random amount of time before repeating the sense-and-transmit-when-idle cycle
##### Carrier Sense Multiple Access with Collision Dection (CSMA/CD)
* CSMA/CD operation from the perspective of an adapter in a node attached to a broadcast channnel
  1. The adapter obtains a datagram from the network layer, prepares a link-layer frame, and puts the frame adapter buffer
  2. If the adapter senses that the channel is idle, it starts to transmit the frame. If the adapter senses that the channel is busy, it waits until it senses no signal energy and then starts to transmit the frame
  3. When transmitting, the adapter monitors for the presence of signal energy coming from other adapters using the broadcast channel
  4. If the adapter transmits the entire frame without detecting signal energy from the other adapters, the adapter is finished with the frame. If, on the other hand, the adapter detects signal energy from other adapters while transmitting, it aborts the transmission
  5. After aborting, the adapter waits a random amount of time and then returns to step 2
##### CSMA/CD Efficiency
* Efficiency = 1/(1 + 5d<sub>prop</sub>/d<sub>trans</sub>)
#### 5.3.3 Taking-Turns Protocols
* Two desirable properties of a multiple access protocol are: 
  1. When only one node is active, the active node has a throughput of R bps
  2. When M nodes are active, then each active node has a throughput of nearly R/M bps
  * The ALOHA and CSMA protocols have this first property but not the second
* This motivated the creation of taking-turns protocols
  1. Polling protocol: one of the nodes to be designated as a master node. The master node polls each of the nodes in a round-robin fashion. In particular, the master node first sends a message to node 1, saying that it (node 1) can transmit up to some maximum number of frames. After node 1 transmits some frames, the master node tells node 2 it (node 2) can transmit up to the maximum number of frames. (The master node can determine when a node has finished sending its frames by observing the lack of a signal on the channel.) The procedure continues in this manner, with the master node polling each of the nodes in a cyclic manner.
     * Drawbacks: introduces a polling delay. Also, if the master node fails, the entire channel fails
  2. Token-passing protocol: A small, special-purpose frame known as a token is exchanged among the nodes in some fixed order. For example, node 1 might always send the token to node 2, node 2 might always send the token to node 3, and node N might always send the token to node 1. When a node receives a token, it holds onto the token only if it has some frames to transmit; otherwise, it immediately forwards the token to the next node. If a node does have frames to transmit when it receives the token, it sends up to a maximum number of frames and then forwards the token to the next node.
     * Drawbacks: The failure of one node can crash the entire channel. If a node neglects to release the token, then some recovery procedure must be invoked to get the token back in circulation
### 5.4 Switched Local Area Networks
#### 5.4.1 Link-Layer Addressing and ARP
* Hosts and routers have link-layer addresses, just as they have network-layer addresses
##### MAC Addresses
* A link-layer address is variously called a LAN address, a physical address, or a MAC address
##### Address Resolution Protocol (ARP)
* Because there are both network-layer addresses (for example, Internet IP addresses) and link-layer addresses (that is, MAC addresses), there is a need to translate between them. For the Internet, this is the job of the Address Resolution Protocol (ARP)
* An ARP module in the sending host takes any IP address on the same LAN as input, and returns the corresponding MAC address
* Each host and router has an ARP table in its memory which contains mappings of IP addresses to MAC addresses. The ARP table also contains a time-to-live (TTL) value, which indicates when each mapping will be deleted from the table
* First, the sender constructs a special packet called an ARP packet. An ARP packet has several fields, including the sending and receiving IP and MAC addresses. Both ARP query and response packets have the same format. The purpose of the ARP query packet is to query all the other hosts and routers on the subnet to determine the MAC address corresponding to the IP address that is being resolved
#### 5.4.2 Ethernet
##### Ethernet Frame Structure
* [Ethernet frame structure](http://fschub.com/wp-content/uploads/2017/03/ethernet-II.jpg)
#### 5.4.3 Link-Layer Switches
* The switch itself is transparent to the hosts and routers in the subnet; that is, a host/router addresses a frame to another host/router (rather than addressing the frame to the switch) and happily sends the frame into the LAN, unaware that a switch will be receiving the frame and forwarding it.
##### Forwarding and Filtering
* *Filtering* is the switch function that determines whether a frame should be forwarded to some interface or should just be dropped. 
* *Forwarding* is the switch function that determines the interfaces to which a frame should be directed, and then moves the frame to those interfaces. Switch filtering and forwarding are done with a *switch table*.
##### Self-Learning
* In other words, switches are self-learning. This capability is accomplished as follows:
  1. The switch table is initially empty.
  2. For each incoming frame received on an interface, the switch stores in its table the MAC address in the frame’s source address field, the interface from which the frame arrived, and (3) the current time. In this manner the switch records in its table the LAN segment on which the sender resides. If every host in the LAN eventually sends a frame, then every host will eventually get recorded in the table.
  3. The switch deletes an address in the table if no frames are received with that address as the source address after some period of time (the aging time). In this manner, if a PC is replaced by another PC (with a different adapter), the MAC address of the original PC will eventually be purged from the switch table.
* Switches are *plug-and-play* devices because they require no intervention from a network administrator or user
##### Properties of Link-Layer Switching
* Advantages of using switches:
  * Elimination of collisions. In a LAN built from switches (and without hubs), there is no wasted bandwidth due to collisions! The switches buffer frames and never transmit more than one frame on a segment at any one time. As with a router, the maximum aggregate throughput of a switch is the sum of all the switch interface rates. Thus, switches provide a significant performance improvement over LANs with broadcast links.
  * Heterogeneous links. Because a switch isolates one link from another, the different links in the LAN can operate at different speeds and can run over different media. For example, the uppermost switch in Figure 5.22 might have three 1 Gbps 1000BASE-T copper links, two 100 Mbps 100BASE-FX fiber links, and one 100BASE-T copper link.
  * Management. In addition to providing enhanced security (see sidebar on Focus on Security), a switch also eases network management. For example, if an adapter malfunctions and continually sends Ethernet frames (called a jabbering adapter), a switch can detect the problem and internally disconnect the malfunctioning adapter. With this feature, the network administrator need not get out of bed and drive back to work in order to correct the problem.
#### 5.4.4 Virtual Local Area Networks (VLANs)
* Modern institutional LANs are often configured hierarchically, with each workgroup (department) having its own switched LAN connected to the switched LANs of other groups via a switch hierarchy. While such a configuration works well in an ideal world, the real world is often far from ideal. Three drawbacks can be identified:
  1. Lack of traffic isolation. Although the hierarchy localizes group traffic to within a single switch, broadcast traffic (e.g., frames carrying ARP and DHCP messages or frames whose destination has not yet been learned by a selflearning switch) must still traverse the entire institutional network. Limiting the scope of such broadcast traffic would improve LAN performance. Perhaps more importantly, it also may be desirable to limit LAN broadcast traffic for security/privacy reasons.
  2. Inefficient use of switches. If instead of three groups, the institution had 10 groups, then 10 first-level switches would be required. If each group were small, say less than 10 people, then a single 96-port switch would likely be large enough to accommodate everyone, but this single switch would not provide traffic isolation.
  3. Managing users. If an employee moves between groups, the physical cabling must be changed to connect the employee to a different switch. Employees belonging to two groups make the problem even harder.
* Each of these difficulties can be handled by a switch that supports virtual local area networks (VLANs). As the name suggests, a switch that supports VLANs allows multiple virtual local area networks to be defined over a single physical local area network infrastructure
* A more scalable approach to interconnecting VLAN switches is known as *VLAN trunking*
### 5.5 Link Virtualization: A Network as a Link Layer
#### 5.5.1 Multiprotocol Label Switching (MPLS)
* [MPLS header](http://blog.internetworkexpert.com/wp-content/uploads/2010/02/Screen-shot-2010-02-21-at-2.18.06-PM.png)
* An MPLS-capable router is often referred to as a label-switched router, since it forwards an MPLS frame by looking up the MPLS label in its forwarding table and then immediately passing the datagram to the appropriate output interface.
### 5.6 Data Center Networking
* Each data center has its own *data center network* that interconnects its hosts with each other and interconnects the data center with the Internet
##### Load Balancing
* Inside the data center, the external requests are first directed to a load balancer whose job it is to distribute requests to the hosts, balancing the load across the hosts as a function of their current load
##### Hierarchical Architecture
* A data center often employs a hierarchy of routers and switches
### 5.7 Retrospective: A Day in the Life of a Web Page Request
#### 5.7.1 Getting Started: DHCP, UDP, IP, and Ethernet
* When Bob first connects his laptop to the network, he can’t do anything (e.g., download a Web page) without an IP address. Thus, the first network-related action taken by Bob’s laptop is to run the DHCP protocol to obtain an IP address, as well as other information, from the local DHCP server:
1. The operating system on Bob’s laptop creates a DHCP request message (Section 4.4.2) and puts this message within a UDP segment (Section 3.3) with destination port 67 (DHCP server) and source port 68 (DHCP client). The UDP segment is then placed within an IP datagram (Section 4.4.1) with a broadcast IP destination address (255.255.255.255) and a source IP address of 0.0.0.0, since Bob’s laptop doesn’t yet have an IP address.
2. The IP datagram containing the DHCP request message is then placed within an Ethernet frame (Section 5.4.2). The Ethernet frame has a destination MAC addresses of FF:FF:FF:FF:FF:FF so that the frame will be broadcast to all devices connected to the switch (hopefully including a DHCP server); the frame’s source MAC address is that of Bob’s laptop, 00:16:D3:23:68:8A
3. The broadcast Ethernet frame containing the DHCP request is the first frame sent by Bob’s laptop to the Ethernet switch. The switch broadcasts the incoming frame on all outgoing ports, including the port connected to the router.
4. The router receives the broadcast Ethernet frame containing the DHCP request on its interface with MAC address 00:22:6B:45:1F:1B and the IP datagram is extracted from the Ethernet frame. The datagram’s broadcast IP destination address indicates that this IP datagram should be processed by upper layer protocols at this node, so the datagram’s payload (a UDP segment) is thus demultiplexed (Section 3.2) up to UDP, and the DHCP request message is extracted from the UDP segment. The DHCP server now has the DHCP request message.
5. Let’s suppose that the DHCP server running within the router can allocate IP addresses in the CIDR (Section 4.4.2) block 68.85.2.0/24. In this example, all IP addresses used within the school are thus within Comcast’s address block.
6. The Ethernet frame containing the DHCP ACK is sent (unicast) by the router to the switch. Because the switch is self-learning (Section 5.4.3) and previously received an Ethernet frame (containing the DHCP request) from Bob’s laptop, the switch knows to forward a frame addressed to 00:16:D3:23:68:8A only to the output port leading to Bob’s laptop.
7. Bob’s laptop receives the Ethernet frame containing the DHCP ACK, extracts the IP datagram from the Ethernet frame, extracts the UDP segment from the IP datagram, and extracts the DHCP ACK message from the UDP segment. Bob’s DHCP client then records its IP address and the IP address of its DNS server. It also installs the address of the default gateway into its IP forwarding table (Section 4.1). Bob’s laptop will send all datagrams with destination address outside of its subnet 68.85.2.0/24 to the default gateway. At this point, Bob’s laptop has initialized its networking components and is ready to begin processing the Web page fetch. (Note that only the last two DHCP steps of the four presented in Chapter 4 are actually necessary.)
## Chapter 6: Wireless and Mobile Networks
### 6.1 Introduction
* Elements of a wireless network:
  * Wireless hosts. As in wired networks, these are the end-systems that run applications
  * Wireless links. A host connects to a base station or to another host via a wireless communication link
  * Base station. Responsible for sending and receiving data to and from a wireless host that is associated with the base station. There are no counterparts to these in wired networks. Examples include cell towers and access points
* Hosts associated with a base station are said to be operating in *infrastructure mode*
  * In *ad hoc networks*, hosts have no infrastructure with which to connect. The hosts themselves provided for routing, addres assignment, DNS-like name translation, and more
* *Handoff*: when a host moves beyond the range of one base station and into another
* Networks can be classified according to two criteria: (1) whether a packet crosses one or multiple wireless hops, and (2) whether there is infrastructure such as a base station in the network
  * Single-hop, infrastructure based. Have a base station that is connected to a larger wired network, like the Internet. All communication between the base station and a wireless host occurs over a single wireless hop. Examples: 802.11 networks in a classroom, cafe, or library; 3G cell networks
  * Single-hop, infrastructure-less. One of the nodes in the single-hop network may coordinate the transmissions of other nodes. Examples: Bluetooth and 802.11 networks in ad hoc mode
  * Multi-hop, infrastructure-based. Base station is wired to the larger networks. Some wireless nodes may have to relay communication via other nodes in order to communicate via the base station. Example: wireless mesh networks
  * Multi-hop, infrastructure-less. Nodes may have to relay messages among several other nodes to reach a destination. Nodes may also be mobile, with connectivity changing among nodes. Examples: mobile ad hoc networks (MANETs) and vehicular ad hoc networks (VANET)
### 6.2 Wireless Links and Network Characteristics
* Differences between wired link and wireless link
  * Decreasing signal strength (path loss)
  * Interference from other sources (radio sources transmitting on the same frequency)
  * Multipath propagation: portions of the electromagnetic wave reflect and take paths of different length between a sender and receiver, resulting in blurring of received signal
* Signal-to-noise ratio (SNR): strength of the received signal vs. noise in the environment. Measured in dB
  * For a given scheme, the higher the SNR, the lower the bit error rate (BER)
  * For a given SNR, a modulation technique with a higher bit transmission rate (whether in error or not) will have a higher BER
  * Dynamic selection of the physical-layer modulation technique can be used to adapt the modulation technique to channel conditions
* Hidden terminal problem: Suppose that Station A is transmitting to Station B. Suppose also that Station C is transmitting to Station B. With the socalled hidden terminal problem, physical obstructions in the environment (for example, a mountain or a building) may prevent A and C from hearing each other's transmissions, even though A's and C's transmissions are indeed interfering at the destination, B.
#### 6.2.1 CDMA
* Code division multiple access (CDMA) belongs to the family of channel partitioning protocol
  * Each bit sent is encoded by mutiplying the bit by a signal (the code) that changes at a much faster rate (the chipping rate_ than the original sequence of data bits
### 6.3: WiFi 802.11 Wireless LANs
#### 6.3.1 The 802.11 Architecture
* Basic architecture is the *basic service set (BSS)*. A BSS contains one or more wireless stations and a cental base station, known as an access point (AP). Each 802.11 wireless station has a MAC address that is stored in the firmware of the station's adapter. Each AP also has a MAC address
* Wireless LANs that deploy APs are often referred to as *infrastructure wireless LANs*, with the "infrastructure" being the APs along with the wired Ethernet infrastructure that interconnects the APs and a router
* When a network admin installs an AP, the admin assigns a one- or two-word Service Set Identifier (SSID) to the access point
* A *WiFi jungle* is any location where a wireless station receives a sufficiently strong signal from two or more APs
  * A wireless station needs to associate with exactly one AP; only one AP will send data frames to the machine and vice versa
* How does your wireless station associate with a particular AP?
  * APs periodically send beacon frames, each containing the AP's SSID and MAC address
  * The process of scanning channels and listening for beacon frames is known as passive scanning
  * A wireless host can also perform active scanning by broadcasting a probe frame that will be received by all APs within range
#### 6.3.2 The 802.11 MAC Protocol
* Because multiple stations may want to transmit frames at the same time over the same channel, a multiple access protocol is needed to coordinate transmissions
* CSMA with collision avoidance (CSMA/CA): random access protocol for 802.11 inspired by the success of Ethernet random access protocol
  * Unlike the Ethernet protocol, the MAC protocol does not implement collision detection because:
    * The ability to detect collisions requres the ability to send and receive at the same time; this is costly because the strength of the received signal is small compared to the strength of the transmitted signal
    * If the adapter could transmit and listen at the same time, the adapter would still not be able to detect all collisions, due to the hidden terminal problem and fading
* Because wireless LANs do not use collision detection, once a station begins to transmit a frame, it transmits the frame its in entirety
* When a station in a wireless LAN sends a frame, the frame may not reach the destination intact. To deal with this, the 802.11 MAC protocol uses link-layer acknowledgements. When the destination receives a frame that passes the CRC, it waits for a duration (Short Inter-frame Spacing, SIFS) and sends back the ACK frame. If the transmitting station does not receive the ACK within a certain amount of time, it retransmits the frame, using CSMA/CA protocol to access the channel. IF the ACK is not received after a certain number of transmissions, the frame is discarded
##### Dealing with Hidden Terminals: RTS and CTS
* Request to Send (RTS) control frame and Clear to Send (CTS) control frames are sent to reserve access to the channel
#### 6.3.3 The IEEE 802.11 Frame
* [Diagram](http://phoenix.goucher.edu/~kelliher/s2011/cs325/may04img10.png)
1. Frame Control: 
   1. Protocol version: which version of 802.11?
   2. Type and subtype: which type of frame (data, RTS, CTS, beacon, etc)
   3. More frag: link layer fragment indication
   4. Retry: retransmit indication
   5. Power management: inform AP that host will be sleeping to save power
   6. More data: AP informing host not to sleep
2. Duration: length of transmission in microseconds
3. Address 1: Destination MAC
4. Address 2: Source MAC
5. Address 3: MAC address of router inferface attached to AP
6. Sequence control: for fragment reassembly
#### 6.3.5 Advanced Features in 802.11
##### 802.11 Rate Adaption
* Two consecutive retransmits results in backing down to the next lowest transmission rate. 10 successful frames in a row or fallback timer timeout results in increasing to the next highest transmission rate
##### Power Management
* A node that has no frames to send or receive can be asleep 99% of the time, resulting in a significant energy savings
#### 6.3.6 Personal Area Networks: Bluetooth and Zigbee
##### Bluetooth
* Short range, low power, low cost "cable replacement" tech for interconnecting notebooks, peripheral devices, cell phones
* Sometimes referred to as wireless personal area networks (WPANs)
* The link and physical layers of 802.15.1 are based on earlier *Bluetooth* spec for personal area networks
  * Operate in the 2.4 GHz unlicensed radio band in a TDM manner, with time slots of 625 microseconds
    * During each time slot, a sender transmits on one of 79 channels, with the channel changing an a known but pseudo-random manner from slot to slot. This is known as frequency-hopping spread spectrum (FHSS)
* Ad hoc networks: no infrastucture is necessary
* Devices are organized into a piconet of up to eight devices. One device is designated as the master; the rest are slaves
  * Master node clock determines time in piconet, transmits in each odd slot
  * Slaves can only transmit after master has initiated communication in the previous slot, and slaves can only transmit to the master
  * There can also be 255 parked devices in the piconet, which are all inactive until the master changes their status to slave
### 6.4 Cellular Internet Access
#### 6.4.1 An Overview of Cellular Network Architecture
##### Cellular Network Architecture, 2G: Voice Connections to the Telephone Network
* "Cellular" refers to the fact that the region covered by a cell network is partitioned into a number of geographic coverage areas (cells)
  * Each cell contains a base transceiver station (BTS) that transmits signals to and receives signls from the mobile stations in its cell
* GSM standard for 2G cell systems used combined FDM/TDM radio for the air interface
  * The channel is partitioned into a number of frequency sub-bands; within each sub-band, time is partitioned into frames and slots
* A GSM network's base station controller (BSC) will service several dozens of base tranceiver stations
  * BSC allocates BTS radio channels to mobile subscribers, performs paging (finds the cell in which a mobile user is located), and performs handoffs of mobile users
  * Base station controller and its controlled base transceiver stations constitute a GSM Base Station System (BSS)
* Mobil
#### 6.4.2 3G Cellular Data Networks: Extending the Internet to Cellular Subscribers
##### 3G Core Network
* Leave the existing core GSM cell voice network untouched, adding additional cellular data functionality in parallel to the existing cellular voice network
* Types of nodes in 3G core:
  * Serving GPRS Support Nodes and Gateway GPRS Support Nodes
##### 3G Radio Access Network: The Wireless Edge
* Wireless first-hop network that we see as 3G users
#### 6.4.3 On to 4G: LTE
* Evolved packet core (EPC): simplified all-IP core network that unifies separate circuit-switched cell voice network and the packet-switched cell data network. Both voice and data are carried in IP datagrams
* LTE radio access network: combines frequency division multiplexing and time division multiplexing on the downstream channel. Each active mobile node is allocated one or more 0.5 ms time slots in one or more of the channel frequencies; a mobile node is able to achieve increasingly higher transmission rates. Uses sophisticated multiple output antennas
### 6.5 Mobility Management: Principles
* The permanent home of a mobile node (such as a laptop or phone) is known as the home network
* The entity within the home network that performs mobility management functions is known as the home agent
* The network in which the mobile node is residing is known as the foreign (or visited) network
* Entity within the foreign network that helps mobile node with mobility management is foreign agent
* A correspondent is the entity that wishes to communicate with the mobile node
#### 6.5.1 Addressing
* Locate foreign agents at hthe edge routers in the foreign network
  * Foreign agent creates *care-of address (COA)* for the mobile node; network portion of the COA matches that of the foreign network
* Two addresses associated with a mobile node:
  1. Permanent address
  2. COA (foreign address)
#### 6.5.2 Routing to a Mobile Node
##### Indirect Routing to a Mobile Node
* Correspondent addresses the datagram to the mobile node's permanent address and sends the datagram into the network
* Netowork layer functionality required to support mobility:
  * Mobile node to foreign agent protocol: mobile node registers with foreign agent when attaching to foreign network. Mobile node will deregister with foreign agent when it leaves foreign network
  * Foreign agent to home agent registration protocol. Foreign agent will register the mobile node's COA with the home agent. The foreign agent need not explicitly deregister a COA when a mobile node leaves its network, because the subsequent registration of a new COA will take care of this
  * Home agent datagram encapsulation protocol. Encapsulation and forwarding of the correspondent's original datagram within a datagram addressed to the COA
  * Foreign agent decapsulation protocol. Extraction of the correspondent's original datagram from the encapsulating datagram, and the forwarding of the original datagram to the mobile node
##### Direct Routing to a Mobile Node
* Indirect routing suffers from *triangle routing problem*, datagrams addressed to the mobile node must be routed first to the home agent and then to the foreign netowrk, even when a more efficient route exists between the correspondent and the mobile node
* Direct routing overcomes this, but does this at the cost of additional complexity
  * Corresponding agent in the correspondent's network learns the COA of the mobile node
  * Correspondent agent tunnels datagrams to the mobile node's COA
* Complications of direct routing:
  * Mobile-user location protocol is needed for the correspondent agent to query the home agent to obtain the mobile node's COA
  * When the mobile node moves from one foreign network to another, how will data be forwarded to the new foreign network?
