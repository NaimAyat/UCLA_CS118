# CS 118: Computer Network Fundamentals
## Study Guide for Final Exam, Winter 2018
### Reliable Data Transfer
* Enumerate all the basic mechanisms needed to ensure reliable data transfer.
  * Error detection: checksums
  * Receiver feedback: ACKs and NAKs
  * Retransmission
* Stop-and-wait: transmit one packet at a time. Wait a certain period of time for ACK from receiver. If timeout or corrupted ACK, retransmit packet.
* Go-Back-N: sender transmits N packets without waiting for ACK. When we receive ACK n, we assume all packets before n have been delivered successfully and advance the window; hence, lost ACKs are typically not a problem. Out-of-order packets are discarded. If an ACK in the current window is not received by window timeout, the entire current window is retransmitted.
* Selective repeat: transmit N packets, timing each one. If packet times out before ACK is received, resend the packet. Hence, lost ACKs are now a problem. However, out-of-order packets can now be buffered, so less overhead is spent on unnecessary retransmissions. 
