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
          ```
          GET /index.html HTTP/1.1\r\n
          Host: www-net.cs.umass.edu\r\n
          User-Agent: Firefox/3.6.10\r\n
          Accept: text/html,application/xhtml+xml\r\n
          Accept-Language: en-us,en;q=0.5\r\n
          Accept-Encoding: gzip,deflate\r\n
          Accept-Charset: ISO-8859-1,utf-8;q=0.7\r\n
          Keep-Alive: 115\r\n
          Connection: keep-alive\r\n
          \r\n
          ```
  2. Response
          ```
          HTTP/1.1 200 OK\r\n
          Date: Sun, 26 Sep 2010 20:09:20 GMT\r\n
          
          Server: Apache/2.0.52 (CentOS)\r\n
          
          Last-Modified: Tue, 30 Oct 2007 17:00:02 GMT\r\n
          
          ETag: "17dc6-a5c-bf716880"\r\n
          
          Accept-Ranges: bytes\r\n
          
          Content-Length: 2652\r\n
          
          Keep-Alive: timeout=10, max=100\r\n
          
          Connection: Keep-Alive\r\n
          
          Content-Type: text/html; charset=ISO-8859-1\r\n
          
          \r\n
          ```
## Uploading Form Input
* POST method
  * Web page often includes form input
  * Output is uploaded to server in entity body
* URL method
  * Uses GET method
  * Input is uploaded in URL field of request line
## Method Types
* HTTP/1.0
  * GET
  * POST
  * HEAD
    * Asks server to leave requested object out of response
* HTTP/1.1
  * GET, POST, HEAD
  * PUT
    * Uploads file in entity body to path specified in URL field
  * DELETE
    * Deletes file specified in URL field
