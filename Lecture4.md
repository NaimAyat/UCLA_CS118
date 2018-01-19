# Lecture 4 (Jan 18, 2018)
## Persistent HTTP 
### Non-Persistent HTTP Issues
* Requires 2 RTTs (round-trip delay times) per object
* OS overhead for *each* TCP connection
* Browsers often open parallel TCP connections to fetch referenced objects
### Persistent HTTP
* Server leaves connection open after sending response
* Subsequent HTTP messages between same client/server sent over open connection
* Client sends requests as soon as it encounters a referenced object
* As little as one RTT for all the referenced objects
