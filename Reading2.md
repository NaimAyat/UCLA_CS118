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
