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
     
       
