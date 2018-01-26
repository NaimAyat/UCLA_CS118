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
