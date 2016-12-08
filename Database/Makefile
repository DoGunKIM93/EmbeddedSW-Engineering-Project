CC = gcc
CFLAGS = -g -Wall
OUTPUT = mysqlActive_2
INCLUDEPATH = /usr/include/mysql
LIBPATH = /usr/local/lib/mysql

$(OUTPUT): mysqlActive_2.cpp
	$(CC) $(CFLAGS) -o $(OUTPUT) mysqlActive_2.cpp -I$(INCLUDEPATH) -L$(LIBPATH) -lmysqlclient
