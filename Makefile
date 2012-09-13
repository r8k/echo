debug:
	CFLAGS=-g make -C src

release:
	CFLAGS=-O2 make -C src

clean:
	make clean -C src
