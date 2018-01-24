# Lecture 5 (Jan 23, 2018)
## DNS (Domain Name System)
* Distributed database
  * Implemented in hierarchy of many name servers
  * Example: client wants IP for www.naimayat.me; 1st approximation:
    * Client queries root server to find com DNS server
    * Client queries .me DNS server to get  www.naimayat.me DNS server
    * Client queries www.naimayat.me DNS server to get IP address for www.naimayat.me
### Root Name Servers
* Contacted by local name server that cannot resolve name
* Root name server serves to:
  * Contact authoritative name server if name mapping not known
  * Gets mapping
  * Returns mapping to local name server
### TLD, Authoritative Servers
* Top-Level Domain (TLD) servers:
  * Responsible for com, org, net, edu, aero, jobs, museums, and all top-level country domains (ex. uk, fr, ca, jp)
  * Network Solutions maintains servers for .com TLD
  * Educase for .edu TLD
* Authoritative DNS servers:
  * Organization's own DNS server(s), providing authoritative hostname to IP mappings for organization's named hosts
  * Can be maintained by organization or service provider
### Local DNS Name Server
* Does not strictly belong to hierarchy
* Each ISP (residential ISP, company, university) has one
  * Also called "default name server"
* When host makes DNS query, query is sent to its local DNS server
  * Has local cache of recent name-to-address translation pairs (but may be out of date)
  * Acts as a proxy, forwards query into hierarchy 
### Caching, Updating Records
* Once any name server learns mapping, it caches mapping
  * Cache entries timeout (disappear) after some time (TTL)
  * TLD servers typically cached in local name servers
    * Thus, root name servers not often visited
* Cached entries may be out-of-date (best effor name-to-address translation)
  * If name host changes IP address, may not be known internet-wide until all TTLs expire
* Update/notify mechanisms proposed IETF standard
  * RFC 2136
### DNS Records
* DNS: Distributed database storing resource records (RR)
* RR format: `(name, value, type, ttl)`
  * `type=A`
    * `name` is hostname
    * `value` is IP address
  * `type=NS`
    * `name` is domain (ex. foo.com)
    * `value` is hostname of authoritative name server for this domain
  * `type=CNAME`
    * `name` is alias name for some "canonical" (the real) name
    * `www.ibm.com` is really `servereast.backup2.ibm.com`
    * `value` is canonical name
  * `type=MX`
    * `value` is name of mail server associated with name
### DNS Protocol, Messages
* Query and reply messages, both with same message format
* Message header
  * Identification: 16 bit number for query, reply to query uses same number
  * Flags:
    * Query or reply
    * Recursion desired
    * Recursion available
    * Reply is authoritative
### Attacking DNS
* DDoS attacks
  * Bombard root servers with traffic
    * Not successful to date
    * Traffic filtering
    * Local DNS servers cache IPs of TLD servers, allowing root server bypass
  * Bombard TLD servers
    * Potentially more dangerous
* Redirect attacks
  * Man-in-middle
    * Intercept queries
* DNS poisoning
  * Send bogus replies to DNS server, which caches
* Exploit DNS for DDoS
  * Send queries with spoofed source address: target IP
  * Requires amplification
## Pure P2P Architecture
### File distribution: client-server vs. P2P
* Question: How much time does it take to distribute a file of size F from one server to N peers?
  * Peer upload/download capacity is a limited resource
#### File distribution time: P2P
* Server transmission: must upload at least one copy
  * Time to send one copy: F/u<sub>s</sub>
* Client: each client must download file copy
  * Min client download time: F/d<sub>min</sub>
* Clients: as aggregate must download NF bits
  * Max upload rate (limiting max download rate) is u<sub>s</sub> + Σu<sub>i</sub>
* Takeaway: P2P is more scalable
### BitTorrent
* File divided into 256Kb chunks
* Peers in torrent send/receive file chunks
* Tracker: tracks peers participating in torrent
* Torrent: group of peers echanging chunks of a file
* Peer joining torrent:
  * Has no chunks, but will accumulate them over time from other peers
  * Registers with tracker to get list of peers, connects to subset of peers ("neighbors")
* While downloading, peer uploads chunks to other peers
* Peer may change peers with whom it exchanges chunks
* Churn: peers may come and go
* Once peer has entire file, it may (selfishly) leave or (altruistically) remain in torrent
#### Requesting chunks
* At any given time, different peers have different subsets of file chunks
* Periodically, alice asks each peer for list of chunks that they have
* Alice requests missing chunks from peers, rarest first
#### Sending chunks: tit-for-tat
* Alice sends chunks to those four peers currentl sending her chunks at highest rate
  * Other peers are choked by Alice (do not receive chunks from her)
  * Re-evaluate top four every 10 secs
* Every 30 secs: randomly select another peer, peer starts sending chunks
  * "Optimisitically unchoke" this peer
  * Newly chosen peer may join top four
## Video Streaming and CDNs
### Context
* Video traffic: major consumer of Internet bandwidth
  * Netflix, YouTube: 37%, 16% of downstream residential ISP traffic
  * ~1B YouTube users, ~75m Netflix Users
### Video
* Sequence of images displayed at a constant rate
* Digital image: array of pixels, each pixel represented by bits
* Coding: use redundancy within and between images to decrease number of bits used to encode image
  * Spatial (within image)
  * Temporal (from one image to next)
  
