# Lecture 4 (Jan 18, 2018)
## Persistent vs. Non-Persistent HTTP 
### Non-Persistent HTTP Issues
* Requires 2 RTTs (round-trip delay times) per object
* OS overhead for *each* TCP connection
* Browsers often open parallel TCP connections to fetch referenced objects
### Persistent HTTP
* Server leaves connection open after sending response
* Subsequent HTTP messages between same client/server sent over open connection
* Client sends requests as soon as it encounters a referenced object
* As little as one RTT for all the referenced objects
## HTTP Request Message
* Two types of HTTP messages:
  1. Request
     * ASCII (human-readable format)
     
  2. Response
  
## Uploading Form Input
* POST method
  * Web page often includes form input
  * Output is uploaded to server in entity body
* URL method
  * Uses GET method
  * Input is uploaded in URL field of request line
