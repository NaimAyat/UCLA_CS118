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
 1. Delay: How responsive is the network?
 1. Loss: How good is packet delivery?
 * How do loss and delay occur?
   * Packets queue in router buffers
     * Packet arrival rate to link exceeds output link capacity
     * Packets queue, wait for turn
 * Four sources of packet delay
   1. Nodal processing
     * Check bit errors
     * Determine output link
   2. Queueing
     * Time waiting at output link for transmission
     * Depends on congestion level of router
