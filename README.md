# NetworkServer
NetworkServer is the multifunctional server (now works as only basic Web server).
It's developed by C++ with CLion.

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
* "Prefork" multiprocess model (default 10 process).
* IPv4 / IPv6 compatible.
* HEAD method returns ony header.
* GET and POST method works the same.
* Other method returns 405 "Method Not Allowed".

## Logging
* Access log output at "resource/webserver/log/access.log"
* Log format:
    * process ID
    * IP address:Listening port (IP protocol)
    * request accept time
    * HTTP protocol version
    * HTTP method
    * request URI
    * HTTP status code
    * User-Agent

## Configuration
User configuration system is under developing.
* Default listening port is 8080 (not need "root" privileges).
* Default prefork process num is 10 .

## Requirement
* OS: MacOS or Linux