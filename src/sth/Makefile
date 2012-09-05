CFLAGS=-I$(HOME)/usr/local/include \
			 -I../utils \
			 -L$(HOME)/usr/local/lib 

LDFLAGS=-lev

all: echo_server
echo_server: echo_server.o ../utils/netutils.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm -rf echo_server *.o
