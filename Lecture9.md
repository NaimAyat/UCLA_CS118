# Lecture 9 (Feb 8 2018)
## TCP Slow Start
* When connection begins, increase rate exponentially when `cwnd<ssthresh`
  * Double `cwnd` every RTT by setting `cwnd += 1 MSS` for every ACK received
* Summary: initial rate is slow but ramps up exponentially 
## Fast Retransmit / Fast Recovery
* Fast retransmit: to detect and repair loss, based on incoming duplicate ACKs
  * Use 3 duplicate ACKs to infer packet loss
  * Set `ssthresh = cwnd/2`
  * `cwnd = ssthresh + 3MSS`
  * Retransmit the lost packet
* Fast recovery: governs the transmission of new data until a non-duplicate ACK arrives
  * Increase cwnd by 1 MSS upon every duplicate ACK
#### Philosophy
* 3 duplicate ACKs to infer losses and differentiate from transient out-of-order delivery
* Receiving each duplicate ACK indicates one more packet left at the network and arrived at the receiver
