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
