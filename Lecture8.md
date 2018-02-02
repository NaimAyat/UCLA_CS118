# Lecture 8 (Feb 2, 2018)
## TCP
### Overview
* Point-to-point
  * One sender, one receiver
* Reliable, in order byte stream
  * No "message boundaries"
* Pipelined
  * TCP congestion and flow control set window size
* Full duplex data
  * Bi-directional data flow in same connection
  * MSS: Maximum segment size
* Connection-oriented
  * Handshaking (exchange of control messages) inits sender, receiver state before data exchange
* Flow controlled:
  * Sender will not overwhelm receiver
