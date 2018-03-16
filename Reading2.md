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
