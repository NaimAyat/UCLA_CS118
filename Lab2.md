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
   
