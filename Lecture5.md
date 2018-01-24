# Lecture 5 (Jan 23, 2018)
## DNS (Domain Name System)
* Distributed database
  * Implemented in hierarchy of many name servers
  * Example: client wants IP for www.naimayat.me; 1st approximation:
    * Client queries root server to find com DNS server
    * Client queries .me DNS server to get  www.naimayat.me DNS server
    * Client queries www.naimayat.me DNS server to get IP address for www.naimayat.me
