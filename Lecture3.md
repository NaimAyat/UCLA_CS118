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
 * Sockets
   * Process sends/receives messages to/from its socket
   * Socket analogous to door
     * Sending process shoves message out door
     * Sending process relies on transport infrastructure on other side of door which brings message to socket at receiving process
   * API
     1. Choice of transport protocol
     2. Ability to fix a few parameters
 * Addressing processes
   * To receive messages, process must have *identifier*
   * Host device has unique 32-bit IP address
   * Does IP address of host on which process runs suffice for identifying the process?
     * No, many processes can be running on the same host
   * Identified includes both *IP addresses* and *port numbers* associated with process on host
   * Example port numbers:
     * HTTP server: 80
     * Mail server: 25
 * App-layer protocol defines
   * Types of messages exhanged
     * Ex. Request, response
   * Message syntax
     * What fields in messages and how fields are delineated
   * Message semantics
     * Meaning of information in fields
   * Rules for when and how processes send and respond to messages
   * Public-domain protocols
     * Defined in RFCs
     * Allows for interoperability
     * Ex. HTTP, SMTP
   * Proprietary protocols
     * Ex. Skype
* What transport service does an app need?
  * Data loss
    * Some apps (ex. audio) can tolerate some loss
    * Other apps (ex. file transfer, telnet) require 100% reliable data transfer
  * Timing
    * Some apps (ex. Internet telephony, interactive games) require low delay to be "effective"
  * Throughput
    * Some apps (ex. multimedia require minimum amount of throughput to be "effective"
    * Other apps ("elastic apps") make use of whatever throughput they get
  * Security
    * Encryption, data integrity
* [Transport Service Requirements of Common Apps](https://www.cs.umd.edu/~shankar/417-F01/Slides/chapter2a-aus/img007.gif)
* Internet Transport Protocol Services
  * TCP service:
    * Connection-oriented: setup required between client and server processes
    * Reliable transport between sending and receiving processes
    * Flow control: sender won't overwhelm receiver
    * Congestion control: throttle sender when network is overloaded
    * Does not provide: timing, minimum throughput guarantees, security
  * UDP service:
    * Unreliable data transfer between sending and receiving process
    * Does not provide: connection setup, reliability, flow control, congestion control, timing, throughput guarantee, or security
