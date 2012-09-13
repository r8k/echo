CFLAGS=-g -Wall -Werror \
			 -I$(HOME)/usr/local/include \
			 -I../utils \
			 -L$(HOME)/usr/local/lib \
			 -L../utils

LDFLAGS=-lev -lutils

all: echo_server
echo_server: echo_server.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm -rf echo_server *.o
