# Lab 3 (Jan 26, 2018)
### Distributed Hierarchical Database
* Client queries a root server to find com DNS server
* Client queries com DNS server to get `amazon.com` DNS server
* Client queries amazon.com DNS server to get IP address for `www.amazon.com`
### DNS Query Process
* Host wants IP address for gaia.cs.umass.edu
* Iterated query
* [Graph of query process](http://images.slideplayer.com/25/8272948/slides/slide_4.jpg)
## Transport Layer
### Transport Services
* Transport protocols run on end systems
  * Sender side: breaks app messages into segments, passes to network layer
  * Receiver side: reassembles segments into messages, passes to app layer
### Transport vs. Network
* Network layer: logical communication between hosts
* Transport layer: logical communication between processes
  * Relies on, enhances, network layer services
* Household analogy: 12 kids in Ann's house sending letters to 12 kids in Bill's house
  * Hosts = houses
  * Processes = kids
  * App messages = letters in envelopes
  * Transport protocol = Ann and bill who demux to in-house siblings
  * Network-layer protocol = postal service
### Multiplexing, Demultiplexing
* Multiplexing at send host: gather data from multiple sockets
* Demultiplexing at receiving host: deliver received segments to the right socket
* Connectionless vs. connection-oriented
  * UDP uses destination port + addresss
  * TCP uses 4-tuple to identify
### UDP
* Connections transport
  * No handshaking
  * Best effort, no delivery guarantee
  * Usage: streaming, DNS, etc.
* Has checksum to detect failure
```
UDP HEADER FORMAT: 

             32 Bits
<------------------------------->
|  source port  |   dest port   |
--------------------------------
|     length    |   checksum    |
---------------------------------
```
### TCP
* Properties of TCP
  * Reliable transfer
  * In-order delivery
  * Flow control and congestion control
* How can we enable these properties at the host?
* [TCP header format](http://telescript.denayer.wenk.be/~hcr/cn/idoceo/images/tcp_header.gif)
