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
