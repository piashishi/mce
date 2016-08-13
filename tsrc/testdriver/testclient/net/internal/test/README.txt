tcpgate.pl can be used for helper in case of serial port is used as TestClient control channel. 

The script is waiting at certain port for incoming tcp connections (client) and routes them to other tcp port (gated). Traffic is routed between these two ports. 
Some other software, responsible of tcp to serial conversion, should be waiting at gated port. There's shareware software for tcp to serial conversion (e.g TCPTOSER).

The script takes care of removing unwanted data which can be caused for example by serial communication handshakes etc. Also ttcn end testcase handling
is taken care of in cases where client disconnects abruptly. Without help, TestClient would never know that test case has ended since serial communication
cannot handle it.

Usage:

tcpgate.pl [client addr] [client port] [gated addr] [gated port]

tcpgate.pl 172.1.1.1 5070 172.2.2.2 5080