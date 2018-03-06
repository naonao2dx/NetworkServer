# WebServer
WebServer is the multifunctional server (now works as only basic HTTP server).  
It's developed by C++.

## Quick Start
### Build
* Clone the repository.
* Build by CMake.

### Command
#### As foreground process
* Start server: $ ./WebServer console
* Stop server: ctrl + c

#### As daemon process
* Start server: $ ./WebServer start
* Stop server: $ ./WebServer stop

#### Check
* Access from  web browser to "http://localhost:8080".

## Configuration
Configuration control by the conf file is under developing.  
* "prefork" multiprocess model (10 process).
* Listening port is 8080 (not need "root" privileges).
* HEAD method returns ony header.
* GET and POST method works the same.
* Other method returns 405 "Method Not Allowed".