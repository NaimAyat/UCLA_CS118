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
* Upon 3rd duplicate ACK
  * `ssthresh = max(cwnd/2, 2*MSS)`
    * `cwnd` should be flight size to be more accurate
  * `cwnd = ssthresh + 3*MSS`
  * Retransmit the lost TCP packet
* Upon each additional duplicate ACK
  * `cwnd += 1 MSS`
  * Transmit a new packet if allowed by the updated `cwnd` and `rwnd`
* Upon a new (ie. non-duplicate) ACK
  * `cwnd = ssthresh`
    * Deflating the congestion window size
### Congestion Avoidance
* Increase `cwnd` by 1 MSS per RTT until congestion (loss) is detected
  * Conditions: when `cwnd > ssthresh` and no loss occurs
  * Actions: `cwnd += (MSS/cwnd)*MSS` (bytes) upon every incoming non-duplicate ACK
#### Philosophy
* 3 duplicate ACKs to infer losses and differentiate from transient out-of-order delivery
* Receiving each duplicate ACK indicates one more packet left at the network and arrived at the receiver
