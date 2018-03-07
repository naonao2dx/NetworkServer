# NetworkServer
NetworkServer is the multifunctional server (now works as only basic Web server).
It's developed by C++.

## Quick Start
### Build
* Clone the repository.
* Build by CMake.

### Command
#### As foreground process
* Start server: $ ./NetworkServer console
* Stop server: Enter "ctrl + c" command

#### As daemon process
* Start server: $ ./NetworkServer start
* Stop server: $ ./NetworkServer stop

#### Check
* Access from  web browser to "http://localhost:8080".

## Features 
* "prefork" multiprocess model (10 process).
* Listening port is 8080 (not need "root" privileges).
* HEAD method returns ony header.
* GET and POST method works the same.
* Other method returns 405 "Method Not Allowed".

## Logging
* Access log output at "resource/webserver/log/access.log"