# Lecture 10 (Feb 13, 2018)
##### Midterm
* Covers chapters 1-3; no need to memorize all TCP connections
## Router Architecture
### Output Ports
* Buffering required when datagrams arrive from fabric faster than the transmission rate
* Scheduling discipline chooses among queued datagrams for transmission
#### How much buffering?
* RFC 3439 rule of thumb: average buffering equal to typical RTT times link capacity C
* Recent recommendation: with N flows, buffering = `RTT*C/sqrt(N)`
### Scheduling Mechanisms
* Scheduling: choose next packet to send on link
* FIFO scheduling: send in order of arrival to queue
  * Discard policy: if packet arrives to full queue: who to discard?
    * Tail drop: drop arriving packet
    * Priority: drop/remove on priority basis
    * Random: drop/remove randomly
