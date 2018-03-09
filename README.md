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
* Stop server: Enter "Ctrl + c" command

#### As daemon process
* Start server: $ ./NetworkServer start
* Stop server: $ ./NetworkServer stop

#### Check
##### WebServer
* Access from  web browser to "http://localhost:8080".

## Features
#### WebServer
* "Prefork" multiprocess model (default 10 process).
* IPv4 / IPv6 compatible.
* HEAD method returns ony header.
* GET and POST method works the same.
* Other method returns 405 "Method Not Allowed".

## Logging
#### WebServer
* Access log default output: "resource/webserver/log/access.log"
    * Log format:
        * process ID
        * IP address:Client port (IP protocol)
        * request accept time
        * HTTP protocol version
        * HTTP method
        * request URI
        * HTTP status code
        * User-Agent

## Configuration
#### WebServer
Configuration file path: "resource/webserver/config/webserver.conf"
* ListeningPort  (Default is 8080. Not need "root" privileges).
* StartServer: Prefork process num (Default is 10).
* AccessLogFilePath

## Requirement
* OS: MacOS or Linux