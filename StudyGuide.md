# CS 118: Computer Network Fundamentals
## Study Guide for Final Exam, Winter 2018
### Reliable Data Transfer
1. Enumerate all the basic mechanisms needed to ensure reliable data transfer.
   * Error detection: checksums
   * Receiver feedback: ACKs and NAKs
   * Retransmission
2. Stop-and-wait: transmit one packet at a time. Wait a certain period of time for ACK from receiver. If timeout or corrupted ACK, retransmit packet.
3. Go-Back-N: sender transmits N packets without waiting for ACK. The receiver only sends a cumulative ACK, meaning that all packets up to n have been received. Out-of-order packets are discarded. If the ACK is not received, the entire current window is retransmitted.
4. Selective repeat: transmit N packets, timing each one. Individual ACKs for each packet. If packet times out before ACK is received, resend the packet. Out-of-order packets can now be buffered, so less overhead is spent on unnecessary retransmissions. 
### TCP Protocol
1. TCP round-trip estimation and timeout [**See Homework 4, Problem 4**]
2. Is SampleRTT computer for a segment that has been retransmitted? Why?
   * No, when its ACK arrives it is impossible to know if this is ACK was from the first transmission or from a retransmission. Thus, this could ruin our value of RTT.
3. What is the negative effect if the timeout value is too small? Too big?
   * If it is too small, then overhead will be spent on unnecessary retransmissions. If it is too big, we will waste an unecessary amount of time waiting for ACKs that are never going to arrive.
4. Why does sampleRTT fluctuate?
   * SampleRTT values will fluctuate from segment to segment due to congestion in the routers and to the varying load on the end systems.
5. How does TCP readjust its timer? 
   * Consider RTT measurements for segments that have not been retransmitted. Every time TCP sends a data segment, it records the transmission time. When the ACK is received, TCP reads the system time again. This difference is called SampleRTT. When we have to retransmit a segment, we set the timer to twice its previous value. Hence, when when TCP time outs repeatedly, the timeout value will increase exponentially.
### TCP Connection Management
1. What is the 3-way handshake? 
  * The client sends SYN packet to the server. The server responds with a SYN-ACK. The client responds with an ACK. The connection is established.
2. How are the initial seq, ACK #, etc. decided?
  * When a TCP connection is established, each side generates a random number as its initial sequence number. This is important, because if sequence or ACK numbers were guessable, this would be a security issue. Thereafter, for every byte transmitted the sequence number will increment by 1. The ACK field is the sequence number from the other side, sent back to acknowledge reception.
3. Are the TCP connection setup and teardown identical? 
  * No, the teardown works as follows: One side of the connection sends a packet with the FIN bit. The other side responds with two packets, an ACK and a FIN of its own. This last fin is ACKed by the original side, indicating the connection has been closed on both sides.
4. Why are there so many states in the FSM model for TCP connection?
   * We need a state to represent each step of the handshake and teardown process. Otherwise, it would be unclear what part of the connection setup or teardown we are currently on. 
### TCP Congestion Control
1. How many components are there in TCP congestion control? 
   * Slow start, congestion avoidance, fast retransmit, fast recovery.
2. How does each component of TCP congestion control work?
   * Slow start:
     * Set `cwnd = maximum segment size (MSS)`
     * When connection begins, increase rate exponentially until cwnd reaches slow start threshold `ssthresh`
     * Double `cwnd` every RTT by setting `cwnd += MSS` for each ACK received
     * Initial transmission rate is slow but ramps up exponentially fast
   * Switching from slow start to congestion avoidance:
     * When `cwnd` gets to half its value before timeout. `ssthresh` is set to half of `cwnd` just before loss event
   * Congestion avoidance:
     * Increase `cwnd` by `1 MSS` per RTT until loss is detected
     * Active when `cwnd > ssthresh` and no loss occurs
     * `cwnd += (MSS/cwnd)*MSS` upon every incoming non-duplicate ACK
   * When loss occurs:
     * Through duplicate ACKS: fast retransmit / fast recovery
     * Through retransmission timeout: reset everything
   * Fast retransmit / Fast Recovery
     * 3 duplicate ACKs infer packet loss
     * `ssthresh = cwnd/2`
     * `cwnd = ssthresh + 3MSS`
     * Retransmit the lost packet
     * Fast recovery: until a non-duplicate ACK arrives, increase `cwnd` by `1 MSS` upon every duplicate ACK
     * Upon 3rd duplicate ACK `ssthresh = max(cwnd/2, 2*MSS)`, `cwnd = ssthresh + 3*MSS`, retransmit lost packet
     * Upon each additional duplicate ACK, `cwnd += 1 MSS`, transmit a new packet if allowed by the updated cwnd and rwnd
     * Upon a new non-duplicate ACK `cwnd = ssthresh`, deflating the congestion window size
   * Retransmission Timeout:
     * When retransmision timer expires, `ssthresh = max(cwnd/2, 2*MSS)`, `cwnd = 1 MSS`, retransmit lost packet
### Network Layer
1. What is the Internet service model?
   * "Best-effort service". Timing between packets is not guaranteed to be preserved, packets are not guaranteed to be in order, and the delivery of packets is not guaranteed.
2. Compare VC (virtual circuit) and datagram networks. 
   * Virtual circuit:
     * Connection-oriented; there is a reservation of resources like buffers, CPU bandwidth, etc. for the time in which a newly setup VC is going to be used by a data transfer session
     * First packet goes and reserves resources for subsequent packets. As a result, all packets follow the same path during the connection
     * Since all packets follow the same path, a global header is required only for the first packet
     * Since all packets follow the same path, packets reach the destination in order
     * Since each time a new connection has to be setup with reservation of resources and routers need to store connection state information, VCs are costly to implement
   * Datagram networks:
     * Connectionless; there is no need to reserve resources as there is no dedicated path
     * Packets are free to travel any path on any intermediate router, which is decided on-the-fly by dynamically changing routing tables on routers
     * All packets must be associated with a header with proper information about the source and upper layer data
     * Packets reach the destination in any order
     * Not as reliable as virtual circuits, but easy to implement and cost-efficient because there are no reserved resources
3. How does a router decide which next hop to forward when a packet arrives?
   * The router's routing table contains the IP address of the destination network and the IP address of the next hop along the path to the final destination. Towards the edges of the Internet, each router has one or more default routes. The default route is used for all destination addresses for which the router doesn't have a specific route, and points "inward" - ie. it is assigned to the router's upstream link. Each packet will therefore tend to flow upstream, towards the core of the network. As you get closer towards the network core, the routers tend to have larger and larger routing tables - they "know about" more networks. The core routers themselves do not have default routes - if they don't know how to get to the destination, they just drop the packet. The routers at this level use BGP to exchange routes with other core routers. If your packet makes it this far, it will then start flowing downstream again, until it reaches its destination.
4. What is the rationale for each field in the IP packet header?
   * IPv4:
     * Version number: 4 bits specify the IP protocol version of the datagram
     * Header length: determines where in the datagram the data actually begins
     * Type of service: allow different types of datagrams to be distinguished (low delay, high throughput, etc.)
     * Datagram length: total length of the datagram, header+data
     * Identifier, flags, fragmentation offset: determines if data is fragmented and needs fixing at intermediate routers
     * Time-to-live: ensures that datagrams do not circulate forever in the network. This is decremented by 1 each time the datagram is processed by a router. If it reaches 0, the datagram is dropped.
     * Protocol: used when the datagram reaches its destination; indicates the transport-layer protcol to which the data portion should be passed
     * Header checksum: aids router in detecting bit errors in a received IP datagram
     * Source and destination IP addresses: to ensure the packet is delivered to the right place
     * Options: allow header to be extended
     * Data: actual information we want to be transmitted
   * IPv6: 
     * Version number: specify the IP version number
     * Traffic class: similar to the type of service field in IPv4
     * Flow label: identifies flow of datagram
     * Payload length: unsigned integer giving the number of bytes in the IPv6 datagram following the fixed length, 40-byte header
     * Next header: similar to the protocol field in IPv4
     * Hop limit: similar to the time-to-live field in IPv4
     * Source and destination addresses: to ensure the packet is delivered to the right place
     * Data: actual information we want to be transmitted
5. Explain IP fragmentation and reassembly.
   * Only offered in routers in IPv4; IPv6 fragmentation and reassembly can only be performed by the source and destination. When a router's outgoing link has a smaller maximum transmission unit than the length of an IP datagram, the datagram is fragmented into two or more smaller IP datagrams, each encapsulated in a separate link-layer frame, and sent over the outgoing link. When the fragments arrive at the destination, the destination host can reassemble the fragments based on the identifier, flags, and fragmentation offset header fields.
6. What is a subnet? 
   * A subet is created by detaching each interface from its host or router, creating islands of isolated networks, with interfaces terminating the end points of the isolated networks. Each of these isolated networks is a subnet. Typically, a subnet may represent all the machines at one geographic location, in one building, or on the same local area network (LAN).
7. What is CIDR? 
   * Classless interdomain routing (CIDR) is the internet's address assignment strategy. The 32-bit IP address is divided into two parts and has the dotted-deciman form a.b.c.d/x, where x is the number of bits in the first part of the address. The x most significant bits of an address of the form a.b.c.d/x constitute the network portion of the IP address, and are often referred to as the prefix (or network prefix) of the address. An organization is typically assigned a block of contiguous addresses, that is, a range of addresses with a common prefix. In this case, the IP addresses of devices within the organization will share the common prefix
8. How does NAT work?
   * The idea is that all hosts residing in a local network do not need to have globally unique addresses for communicating with each other over the network. Instead, a host that is part of the network is assigned a "private address" that is not globally unique, but unique in the local network. If a host wants to communicate outside the local network, the NAT-enabled router translates the host's private address to the globally unique address the NAT-enabled router posesses. When the NAT-enabled router receives IP packets from a host inside its local network, it translates the private address to a globally unique address. Similarly, when packets come from outside the network to the NAT router, the router uses its NAT translation table (which includes port numbers as well as IP addresses) to send the packet to the correct host. 
9. How does DHCP work? 
   * Dynamic Host Configuration Protocol (DHCP) allows hosts to be allocated IP addresses automatically. This is a four-step process. (1) DHCP server discovery: the new host sends a DHCP discover message within a UDP packet to port 67. The UDP packet is encapsulated in an IP datagram. The DHCP client creates an IP datagram containing its DHCP discover message along with the broadcast destination IP address of 255.255.255.255 and a "this host" source IP address of 0.0.0.0. The DHCP client passes the IP datagram to the link layer, which then broadcasts this frame to all nodes attached to the subnet. (2) DHCP server offers: a DHCP server receiving a discover message responds to the client with a DHCP offer message that is broadcasted to all nodes on the subnet, again using the IP broadcast address of 255.255.255.255. Each server offer message contains the transaction ID of the received discover message, the proposed IP address for the client, the network mask, and an IP address lease time. (3) DHP request: the newly arriving client will chose from among one or more server offers and respond to it with a DHCP request message, echoing back the configuration parameters. (4) DHCP ACK: the server responds to the DHCP request message with a DHCP ACK, confirming the request.
10. How does the tunneling technique work?
    * Suppose two IPv6 nodes want to interoperate using IPv6 datagrams, but are connected to each other by intervening IPv4 routers. The intervening IPv4 routers are referred to as the tunnel. The IPv6 node on the sending side of the tunnel takes the entire IPv6 datagram and puts it in the data field of an IPv4 datagram. This IPv4 datagram is then addressed to the IPv6 receiver and sent to the first node in the tunnel. The intervening IPv4 routers send the datagram through the tunnel and to the receiver. The receiver determines that the IPv4 datagram contains an IPv6 datagram, extracts it, and routes it as normal.
11. When you plan to deploy a new network technology on the global Internet, how do you address the issue of incremental deployment?
    * It's simply not feasible to declare an arbitrary transition date, uproot the existing technology, and implement the new version globally. Rather, it is best to configure the new technology such that it can still support interactions with the old one, but encourage people to transition to the new technology ASAP (like we observe with tunneling).
12. Compare link state routing and distance vector routing. 
    * In a link-state routing algorithm, the network topology and all link costs are known. This is accomplished by a link-state broadcast algorithm, wherin each node broadcast link-state packets to all other nodes in the network, with each link-state packet containing the identities and costs of its attached links. Essentially, the link-state algorithm is Dijkstra's algorithm. That is, a start node is designated and set to cost 0. All other nodes in the network are set to cost infinity. While there are unknown nodes left in the network, select the unknown node n with the lowest cost. Mark n as known and update its value. Now, for each node b that is adjacent to n, a = min(a's old cost, n's cost + cost(n,a)).
    * Whereas the LS algorithm is an algorithm using global information, the distance vector algorithm is iterative, asynchronous, and distributed. It is distributed in that each node receives some information from one or more of its directly attached neighbors, performs a calculation, and then distributes the results of its calculation back to its neighbors. It is iterative in that this process continues on until no more information is exchanged between neighbors. Each node x maintains the following info: (1) cost to each neighbor, (2) x's distance vector, containing x's estimate of its cost to all destinations, (3) the distance vectors of each neighbor. When a node. After initialization, each node sends its distance vector to each of its neighbors. After receiving the updates, each node recomputes its own distance vector using Bellman-Ford equation: `Dx(y) ← minv{c(x,v) + Dv(y)}  for each node y ∊ N`. 
13. **Given a network topology, apply link-state routing or distance vector routing algorithm to compute the minimum-cost path (See: [link-state](https://www.youtube.com/watch?v=_lHSawdgXpI) and [distance vector](https://www.youtube.com/watch?v=x9WIQbaVPzY)**)
14. What kind of info is propagated/collected in link state routing or distance vector routing? How many messages are propagated in each?
    * Each link-state packet containing the identities and costs of its attached links. With n nodes and E links, O(nE) messages are sent. In distance vector, messages are sent only when there neighbors have changes in local link costs.
15. What is a potential problem with distance vector routing? How to address it?
    * When a link-cost changes or a link fails, it is possible that distance vector rousing causes a routing loop - packets will bounce between the same nodes indefinitely without getting to their destination. We can acoid this by adding poisoned reverse; when a node routes to another node to get to a destination, the first node will tell the second node that its distance to the destination is infinity, thus preventing the second node from sending the packet back to the first node. 
