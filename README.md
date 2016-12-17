# Basic Client / Server in C

C boilerplate for client / server over network connections.

## Building

    make

## Running

    ./server &
    ./client
    
## In action

    ./server &
    [1] 30377
    server.c: accepting

    ./client
    client.c: sending msg = "hello", n = 5
    server.c: received msg = "hello", n = 5
    client.c: sending msg = "hello", n = 5
    server.c: received msg = "hello", n = 5
    C-c C-cserver.c: bad recv(), restarting
    server.c: accepting


