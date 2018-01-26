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
