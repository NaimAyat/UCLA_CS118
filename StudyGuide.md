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
     * Identifier, flags, fragmentation offset: determines if data is fragmented and needs fixing
     * Time-to-live: ensures that datagrams do not circulate forever in the network. This is decremented by 1 each time the datagram is processed by a router. If it reaches 0, the datagram is dropped.
     * Protocol: used when the datagram reaches its destination; indicates the transport-layer protcol to which the data portion should be passed
     * Header checksum: aids router in detecting bit errors in a received IP datagram
     * Source and destination IP addresses: to ensure the packet is delivered to the right place
     * Options: allow header to be extended
     * Data: actual information we want to be transmitted
     
