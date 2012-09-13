.PHONY: all clean

objs = buffer.o netutils.o connection.o list.o

CFLAGS = -g -Wall -Werror \
				 -I$(HOME)/usr/local/include \
				 -L$(HOME)/usr/local/lib
LDFLAG = -lev
all: libutils.so libutils.a

%.o: %.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

libutils.so: $(objs)
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $^

libutils.a: $(objs)
	ar rc $@ $^

clean:
	rm -rf *.o *.so *.a
