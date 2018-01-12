# Lab 1 (Jan 1, 2018)
## Logistics
### Discussion
* Zhaowei Tan, Discussion 1A
* OH: Wed 3-5 pm @ Boelter 2760
* tan@cs.ucla.edu
### Homework
* Due Wednesdays 6 pm
## Week 1 Concepts
* Internet architecture
  * End systems, communication links, routers
  * Network of networks
    * Private networks connect end systems within the network
      * For example, government end systems can communicate with one another
    * End systems are connected via a core network
      * Packet is sent through wifi or cable
      * End systems are "smart"; core is "dumb"
        * Core has no function other than to transfer packets
        * End systems include PCs, mobile phones, etc.
* Network protocol
  * Layered structure
* Circuit switching vs. packet switching
  * Processing delay, d<sub>process</sub>
    * Created by router reading packet headers to determine where packet should be sent
  * Queuing delay, d<sub>queuing</sub>
    * For each process, there is a FIFO buffer
    * The packets have to wait until the prior packet has been sent
    * Delay comes from waiting in the router buffer
    * When buffer overflows, there are packet drops
    * When there are too many packet drops, the transport speed has to slow down
  * Transmission delay d<sub>transmission</sub>
    * Occurs as router sends packet through link
    * Determined by the link capacity
  * Propagation delay d<sub>propagation</sub>
    * Happens when packets are on the link; the link has a max speed at which packets can travel
* Access systems
  * Multiple devices can connect to a single access point
    * Each device receives a unique ID from access point
    * Access points include wifi routers and cell towers
* ISP (Internet Service Provider)
  1. Packet goes to sender's ISP
  2. If sender's ISP is the same as receiver's ISP, packet goes straight to receiver
  3. If sender's ISP is different from receiver's ISP, packet goes to higher-level ISP
  4. Higher-level ISP sends packet to receiver's ISP
  5. Receiver's ISP sends packet to receiver's end device
* Hierarchy
  1. Application layer
     * Web browser, email client, etc.
  2. Transport layer
     * Congestion
  3. Network layer
     * Routing
  4. Link layer
     * Transmission
  5. Physical layer
     * Cable
## Socket Programming
* Model for network programming
  *  Clients-Server Model
    * Clients request data
      * Initiate communication
      * Send request and wait for server reply
    * Servers respond to data requests
      * Well-known addresses
      * Wait for client connection
      * Process requests and delay
* Abstraction level
  * Clients and servers are both prograps at the application layer
  * Transport layer is responsible for providing communication services
  * The lower layers take care of the rest (routing, transmission, etc.)
  * You can usually choose between two transport protocols
    1. TCP
    2. UDP
