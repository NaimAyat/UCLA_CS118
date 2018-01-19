# Lab 2 (January 1, 2018)
## Socket Programming
* What is the model for network programming? 
  * Client-server
* Where are we programming?
  * At the app layer
## Abstraction Level
* Clients and servers are both programs at the app layer
* Transport layer is responsible for providing communication services
## Application Layer Models
* Application Architectures
  * Client-server model: Web (TCP), FTP (TCP), E-mail (TCP), DNS (UDP/TCP), RTP
  * Peer-to-peer: BitTorrent (TCP), Tor (AKA "Onion Routing", TCP)
  * Hybrid model: Skype (TCP & UDP), GTalk (TCP & UDP)
## Web and HTTP
* Web page consists of objects, addressable by a URL
* HTTP: Hypertext transfer protocol
  * Client/server model
  * Uses TCP, a stateful protocol
  * HTTP itself, however, is stateless (use cookies if we want stateful service)
  * Note: UDP is stateless
## Response Time
* RTT (round-trip delay time): time for a small packet to travel from a client to server and back
* One RTT to initiate TCP connection
* One RTT for HTTP request an first few bytes of HTTP response to return
* File transmission time
* Total = 2RTT + Transmission Time
## Nonpersistent vs. Persistent
* For parallel TCP connections where `n` is the number of objects to transport and `m` is the number of parallel TCP connections:
  * ⌈n/m⌉ = number of RTTs required
### Nonpersistent HTTP
* Requires 2 RTTs per object
* OS overhead for each TCP connection
* Browsers often open parallel TCP connections to fetch referenced objects
### Persistent HTTP
* Server leaves connection open after sending response
* Subsequent HTTP messages between same client/server sent over open connection
* Client sends requests as soon as it encounters a referenced object
* As little as one RTT for all the referenced objects
