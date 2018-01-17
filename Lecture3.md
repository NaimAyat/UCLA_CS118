# Lecture 2 (Jan 16, 2018)
## Chapter 2: Application Layer
* Examples of network apps
  * E-mail
  * Web
  * IM
  * Remote login
  * P2P file sharing
* Creating a network app
  * Write programs that
    * Run on different *end systems*
    * Comunicate over network
    * Ex. Web server software communicates with browser software
  * No need to write software for network-core devices
    * Network-core devices do not run user applications
    * Applications on end systems allows for rapid app development, propagation
* Application architectures
  * Client-server
    * Server
      * Always-on host
      * Permanent IP address
      * Server farms for scaling
    * Client  
      * Communicate with server
      * May be intermittently connected
      * May have dynamic IP addresses
        * Ex. End devices are assigned a different IP each time they access Google search
      * Do not communicate directly with eachother
  * Peer-to-peer
  * Hybrid of client-server and P2P
