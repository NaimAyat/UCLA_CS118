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
    * No always-on server
    * Arbitrary end systems directly communicate
    * Peers are intermittently connected and change IP addresses
    * Highly scalable but difficult to manage
  * Hybrid of client-server and P2P
    * Skype
      * Voice-over-IP P2P application
      * Centralized server: finding address of remote party
      * Client-client connection: direct (not via server)
    * Instant messaging
      * Chatting between two users is P2P
      * Centralized service: client presence detection/location
        * User registers its IP address with central server when it comes online
        * User contacts central server to find IP addresses of friends
   * Processes communicating
     * Process: Program running within a host
     * Within the same host, two processes communicate using inter-process communication (defined by OS)
     * Processes in different hosts communicate by exchanging messages
     * Client process: Process that initiates communication
     * Server process: Process that waits to be contacted
     * Note: applications with P2P architectures have client processes and server processes
