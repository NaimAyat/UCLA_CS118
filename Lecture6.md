# Lecture 6 (Jan 25, 2018)
## Content Distribution Networks
* Challenge: How do we stream conent (selected from millions of videos) to hundreds of thousands of simultaneous users?
  * Option 1: Single, large "mega-server"
    * Single point of failure
    * Point of network congestion
    * Long path to distant clients
    * Multiple copies of video sent over outgoing link
    * This solution doesn't scale
  * Option 2: Store/serve multiple copies of videos at multiple geographically distributed sites (CDN)
    * Enter deep: push CDN servers deep into many access networks
      * Close to users
      * Used by Akamai, 1700 locations
    * Bring home: smaller number (dozens) of larger clusters in POPs near (but not within) access networks
      * Used by Limelight
