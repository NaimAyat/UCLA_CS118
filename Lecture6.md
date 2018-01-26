# Lecture 6 (Jan 25, 2018)
### Content Distribution Networks (CDNs)
* Challenge: How do we stream conent (selected from millions of videos) to hundreds of thousands of simultaneous users?
  * Option 1: Single, large "mega-server"
    * Single point of failure
    * Point of network congestion
    * Long path to distant clients
    * Multiple copies of video sent over outgoing link
    * This solution doesn't scale
  * Option 2: Store/serve multiple copies of videos at multiple geographically distributed sites (CDN)
    * Enter deep: push CDN servers deep into many access networks
      * Close to users
      * Used by Akamai, 1700 locations
    * Bring home: smaller number (dozens) of larger clusters in POPs near (but not within) access networks
      * Used by Limelight
* CDN: stores copies of content at CDN nodes
  * Ex. Netflix stores copies of MadMen
* Subscriber requests conent from CDN
  * Directed to nearby copy, retrieves content
  * May choose different copy if network path congested
* OTT challenges: Coping with a congested internet
  * From which CDN node to retrieve conent?
  * Viewer behavior in presence of congestion?
  * What conent to place in which CDN node?
## Transport Layer
### Transpot Services and Protocols
* Provide logical communication between app processes running on different hosts
* Transport protocols run in end systems
  * Sender side: breaks app messages into segments, passes to network ayer
  * Receiver side: reassembles segments into messages, passes to app layer
* More than one transport protocol available to apps
  * Internet: TCP and UDP
### Internet Transport-Layer Protocols
* Reliable, in-order delivery (TCP)
  * Congestion control
  * Flow control
  * Connection setup
* Unreliable, unordered delivery: UDP
  * No-frills extension of "best-effort" IP
* Services not available:
  * Delay guarantees
  * Bandwidth guarantees
### Multiplexing/Demultiplexing
* Multiplexing at sender: handle data from multiple sockets, add transport header (later used for demultiplexing)
* Demultiplexing at receiver: use header info to deliver received segments to correct socket
#### Demultiplexing (Demux) Breakdown
* Host receives IP datagrams
  * Each datagram has a source IP address, destination IP address
  * Each datagram carries one transport-layer segment
  * Each segment has source, destination port number
* Host uses IP addresses and port numbers to direct segment to appropriate socket
##### Connectionless Demultiplexing
* Recall: created socket has host-local port number
* Recall: when creating datagram to send into UDP socket, must specify
  * Destination IP address
  * Destination port number
* When host receives UDP segment
  * Checks destination port number in segment
    * IP datagrams with same dest, port number, but different source IP address and/or source port number will be directed to the same socket at destination
  * Directs UDP segment to socket with that port number
##### Connection-Oriented Demultiplexing
* TCP socket identified by 4-tuple:
  * Source IP address
  * Source port number
  * Dest IP address
  * Dest port number
* Demux: receiver uses all four values to direct segment to appropriate socket
* Server host may support many simultaneous TCP sockets
  * Each socket defined by its own 4-tuple
* Web servers have different sockets for each connecting client
  * Non-persistent HTTP will have different sockets for each request
