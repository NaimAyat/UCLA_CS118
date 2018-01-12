# Lecture 2 (Jan 11, 2018)
## Packet Switching: Statistical Multiplexing
* Sequence of A & B packets does not have fixed pattern; badwidth is shared on demand
* TDM (Time-Division Multiplexing): Each host gets same slot in revolving TDM frame
* Packet switching vs. circuit switching
  * Packet switching allows more users to use network
    * 1 MB/s link
    * Each user
      * 100kb/s when active
      * Active 10% of the time
  * Circuit switching
    * 10 users
  * Packet switching
    * With 35 users, probability > 10 active at the same time is less than 0.0004
      * 0.0004 
  * Packet switching is good for bursty data
    * Resource sharing
    * Simpler, no call setup
  * Excessive congestion: packet delay and loss
    * Protocols needed for reliable data transfer, congestion control
  * How to provide circuit-like behavior?
    * Bandwidth guarantees needed for audio/video apps
    * Still an unsolved problem
## Performance Metrics
 1. Throughput: How fast?
    * Rate (bits/time) at which bits transferred between sender and receiver.
 2. Delay: How responsive is the network?
 3. Loss: How good is packet delivery?
 * How do loss and delay occur?
   * Packets queue in router buffers
     * Packet arrival rate to link exceeds output link capacity
     * Packets queue, wait for turn
* Four sources of packet delay
  1. Nodal processing
     * Check bit errors
     * Determine output link
  2. Queuing
     * Time waiting at output link for transmission
     * Depends on congestion level of router
* Nodal delay (d<sub>nodal</sub> = d<sub>proc</sub> + d<sub>queue</sub> + d<sub>trans</sub> + d<sub>prop</sub>)
  * d<sub>proc</sub> = processing delay
    * Typically a few microseconds or less
  * d<sub>queue</sub> = queuing delay
    * traffic intensity = L * a / R = Packet size (bits) * Average packet arrival rate / Link bandwidth (bps)
      * L * a / R = 0: average queuing delay is small
      * L * a / R = 1: average queuing delay is large
      * L * a / R > 1: more "work" is arriving than can be serviced; average delay is infinite
    * Depends on congestion
  * d<sub>trans</sub> = transmission delay
    * = L / R = Packet size (bits) / Link bandwidth (bps)
  * d<sub>prop</sub> = propagation delay
    * = d / s = Length of physical link / Propagation speed in medium (~2*10<sup>8</sup> m/s)
    * A few microseconds to hundreds of microseconds
  * What does "real" internet delay and loss look like?
    * Traceroute program: provides delay measurement from source to router
 ## Protocol "Layers"
   * Networks are complex:
     * Composed of many pieces:
       * Hosts
       * Routers
       * Links of various media
       * Applications
       * Protocols
       * Hardware
       * Software
     * How do we standardize/organize them?
       * Layering
         * Dealing with complex systems
           * Explicit structure allows identification, realationship of complex system's pieces
             * Layered reference model
   * Internet protocol stack:
     * Application (top layer): supporting network applications
       * FTP, SMTP, HTTP
     * Transport: process to process data transfer
       * TCP, UDP
     * Network: routing of datagrams from source to destination
       * IP, routing protocols
     * Link: data transfer between neighboring network elements
       * PPP, Ehternet
     * Phyisical (bottom layer): bits on wire
