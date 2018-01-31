# Lecture 7 (Jan 30, 2018)
## rdt2.0: Channel with Bit Errors
* Underlying channel may flip bits in packet
  * Checksum to detect bit errors
* How do we recover from errors?
## Pipelined Protocols
* *Pipelining*: sender allows multiple, "in-flight", yet-to-be-acknowledged packets
  * Range of sequence numbers must be increased
  * Buffering at sender and/or receiver
  * Two generic forms of pipelined protocols:
    1. Go-Back-N
    2. Selective repeat
### Go-Back-N
* Sender can have up to N unacked packets in pipeline
* Receiver only sends cumulative ack
  * Doesn't ack packet if there's a gap
* Sender has timer for oldest unacked packet
  * When timer expires, retransmit all unacked packets
### Selective Repeat
* Sender can have up to N unacked packets in pipeline
* Receiver sends individual ack for each packet
* Sender maintains timer for each unacked packet
  * When timer expires, retransmit only that unacked packet
