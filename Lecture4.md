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
## HTTP Response Status Codes
* Status code appears in 1st line in server-to-client response method
* Examples: 
  * 200 OK
    * Request succeeded, requested object later in this msg
  * 301 Moved Permanently
    * Requested object moved, new location specified later in this msg (Location:)
  * 400 Bad Request
    * Request msg not understood by server
  * 404 Not Found
    * Requested document not found on this server
  * 505 HTTP
    * Version not supported
## Trying HTTP (Client Side) for Yourself
1. Telnet to a Web server:
   * `telnet gaia.cs.umass.edu 80`. 
     * Opens TCP connection to port 80 (default HTTP server port) at gaia.cs.umass.edu. Anything typed in will be sent 
     to port 80 at gaia.cs.umass.edu
 2. Type GET HTTP request
    ```
    GET /kurose_ross/interactive/index.php HTTP/1.1 
    Host: gaia.cs.umass.edu
    ```
3. Look at response message sent by HTTP server
## Stateless HTTP
* In general, HTTP is *stateless*
  * Server maintains no information about past client requests
* Uses TCP
  * Client initiates TCP connection (creates socket) to server, port 80
  * Server accepts TCP connection from client
  * HTTP messages (application-layer protocol messages) exchanged between browser (HTTP client) and Web server (HTTP server)
  * TCP connection closed
## User-Server State: Cookies
* Many Web sites use cookies
* Four components:
  1. Cookie header line of HTTP response message
  2. Cookie header line in next HTTP request message
  3. Cookie file kept on user's host, managed by user's browser
  4. Back-end database at Web site
* Used for:
  * Authorization
  * Shopping carts
  * Recommendations
  * User session state (Web e-mail)
* How to keep "state":
  * Protocol endpoints: maintain state at sender/receiver over multiple transactions
  * Cookies: HTTP messages keep state
* Privacy
  * Cookies permit sites to learn a lot about you
  * You may supply name and e-mail to sites
  * Data can be used for advertising
* Example
  * Naim always accesses Internet from PC
  * Visits specific e-commerce site for first time
  * When initial HTTP requests arrive at site, site creates
    * Unique ID
    * Entry in backend database for ID
## Web Caches (Proxy Server)
Goal: Satisfy client request without involving origin server
* User sets browser: Web accesses via cahce
* Browser sends all HTTP requests to cache
  * Objects in cache: cache returns object
  * Else cache requests object from origin server, then returns object to client
* Cache acts as both client and server
  * Server for original requesting client
  * Client to origin server
* Typically cache is installed by ISP (ex. University, company, residential ISP)
* Why Web caching?
  * reduce response time for client request
  * Reduce traffic on an institution's access link
  * Internet dense with caches: enables "poor" content providers to effectively delever content (so too does P2P file sharing)
## Conditional GET
* Goal: Don't send object if cache has up-to-date cached version
  * No object transmition delay
  * Lower link utilization
* Cache: specify date of cached copy in HTTP request
  ```
  If-modified-since: 
    <date>
  ```
* Server: response contains no object if cached copy is up-to-date
  ```
  HTTP/1.0 304 Not Modified
  ````
## Ongoing Effort on HTTP 2.0
* The next planned version after HTTP1.1 (RFC 2616 in 1999) 
  * 1.4% of Web sites support it (Sept. 2015); 11.4% by Jan 2017
* Designed to improve throughput of client-server connections
* Based on Google's SPDY
* Backward compatible with transaction semantics of HTTP 1.1
* New features: 
  * Multiplexing multiple streams over one HTTP 2.0 connection; request-response pipelining
  * Header compression
  * Server push (preemptive transfer to clients)
## Web 2.0
* No update on the technical specs, more of a marketing idea
* Rather to cumulative changes in the way software developers and users use the Web
* "Network as a platform" computing
  * Build applications on Web, not desktops
* Use rich, user-friendly interfaced based on Ajax and similar clienr-side interactivity tools
## Web 3.0
* Extends the hyperlinked human-readable web pages by inserting machine-readable metadata about pages and how they are related to each other
* Using extensible makeup language (XML), resource description framework (RDF), web ontology language (OWL)
  * XML: syntax for conent structures within documents
  * RDF: expressing data models
  * OWL: adds more vocabularies on describing properties and classes
