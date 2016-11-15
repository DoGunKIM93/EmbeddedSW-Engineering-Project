TARGET := tcpIPServer tcpIPClient
CC = gcc
CFLAGS = -g -Wall
S_OUTPUT = tcpIPServer
C_OUTPUT = tcpIPClient
.PHONY: all clean

all: $(TARGET)

$(S_OUTPUT): tcpIPServer.cpp
	$(CC) $(CFLAGS) tcpIPServer.cpp -o $(S_OUTPUT)
$(C_OUTPUT): tcpIPClient.cpp
	$(CC) $(CFLAGS) tcpIPClient.cpp -o $(C_OUTPUT)
