CC = g++
CFLAGS = -g -Wall
D_OUTPUT = opencvTest
S_OUTPUT = SeeGunners
TARGET = $(D_OUTPUT) $(S_OUTPUT)

all: $(TARGET)

$(D_OUTPUT): opencvTest.cpp
	$(CC) $(CFLAGS) opencvTest.cpp `pkg-config opencv --libs --cflags` -o $(D_OUTPUT)
$(S_OUTPUT): See_gunner.cpp
	$(CC) $(CFLAGS) See_gunner.cpp `pkg-config opencv --libs --cflags` -o $(S_OUTPUT)
