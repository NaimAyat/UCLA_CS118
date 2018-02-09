# Lecture 9 (Feb 8 2018)
## TCP Slow Start
* When connection begins, increase rate exponentially when `cwnd<ssthresh`
  * Double `cwnd` every RTT by setting `cwnd += 1 MSS` for every ACK received
* Summary: initial rate is slow but ramps up exponentially quickly
