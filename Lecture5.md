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
    
