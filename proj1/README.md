# Web Server Implementation Using BSD Sockets
## Design
The server first creates and initializes a socket before listening for and accepting (a maximum of five) connections. It then determines whether the user-inputted port address is open for use. After obtaining a valid port number, a connection is established and a new process is forked to handle the client’s request. The server operates to read in the request message through the socket and print it to the console. 

To fulfill the request, the server obtains the name of the provided file along with its contents and type. This is accomplished by parsing the `GET` request for the relevant information. A `for` loop iterates through the request, splitting the portion following the “ . ” and treating it as an extension. If the filename contains spaces, the `GET` request encoding of space (`%20`) is converted to the space character. The server then checks if the file exists in its own directory. If not, the server returns a `404 Not Found error` and displays a corresponding HTML webpage in the client web browser. Otherwise, the file size is determined by `fseek()` and `ftell()`. 

The server then compares the file extension to the list of supported formats (`.html`, `.htm`, `.jpeg`, `.jpg`, and `.gif`). The response message is constructed by concatenating the accumulated status and header lines; the result is then written to the socket. If the file type is indeed supported, its contents will be displayed in the client web browser. If the file extension is non-existent or unsupported, the file is treated as a binary; that is, the web browser will prompt the user to download it.
## Manual
* To compile the source code, simply type: `make`
* To run the server, type: `./server <port>`
* To test the program, open a web browser to: `http://localhost:<port>/<file>`
