# NetworkServer
NetworkServer is the multifunctional server.  
Now implemented:  
* Web (HTML) server
    * Returns static contents (like html, img, etc)
* API server
    * Returns data from C++ API program

## Quick Start
### Build
* Clone the repository.
    * $ git clone https://github.com/naonao2dx/NetworkServer.git
* Build by CMake.
    * $ cd NetworkServer
    * $ cmake .
    * $ cmake --build ./ --target NetworkServer
    * $ mkdir build
    * $ mv NetworkServer build/
    * $ cd build
    
In the case of Windows, exec file name is NetworkServer.exe
    
### Command
Command: NetworkServer [server] [command]
* WebServer
    * Foreground
        * Start server: $ ./NetworkServer Web console
        * Stop server: Enter "Ctrl + c" command
    * Background (Daemon process)
        * Start server: $ ./NetworkServer Web start
        * Stop server: $ ./NetworkServer Web stop
        
* APIServer
    * Foreground
        * Start server: $ ./NetworkServer API console
        * Stop server: Enter "Ctrl + c" command
    * Background (Daemon process)
        * Start server: $ ./NetworkServer API start
        * Stop server: $ ./NetworkServer API stop

#### Check
##### WebServer
* Access from  web browser to "http://localhost:8080".
##### APIServer
* Access from  web browser to "http://localhost:8081".

## Features
* "Prefork" multiprocess model (default 10 process).
* IPv4 / IPv6 compatible.
* HTTP method
    * HEAD method returns ony response header.
    * GET and POST method returns response header and body.
    * Other method returns 405 "Method Not Allowed".

## Logging
* Access log default output: 
    * WebServer
        * resource/log/web_access.log
    * APIServer
        * resource/log/api_access.log
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
Common configuration file path: "resource/config/NetworkServer.conf".
* ListeningPort: 
    * TCP port. Using well-known port like 80 need root privileges.
* StartServer:
    * Prefork process num (Default is 10).
* AccessLogFilePath

## Requirement
* OS:
    * MacOS
    * Linux
    * Windows (Need Cygwin to compile)