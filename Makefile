OBJS=src/libproc.o src/sleep.o 
TESTS=tests/sleep 
HEADERS=src/libproc.h src/liberror/liberror.h 
CC=cc
PREFIX=/usr/local
LDFLAGS=
LDLIBS=
CFLAGS=-fpic

all: $(OBJS) $(TESTS) libproc.so

clean:
	rm -rf $(OBJS)
	rm -rf $(TESTS)
	rm -rf vgcore.*
	rm -rf core*
	rm -rf libproc.so

install:
	mkdir -p $(PREFIX)
	mkdir -p $(PREFIX)/lib
	mkdir -p $(PREFIX)/include
	mkdir -p $(PREFIX)/include/libproc
	install -m 755 libproc.so $(PREFIX)/lib
	install -m 644 $(HEADERS) $(PREFIX)/include/libproc

uninstall:
	rm -rf $(PREFIX)/include/libproc
	rm -f $(PREFIX)/lib/libproc.so

tests/sleep: tests/sleep.c tests/common.h $(OBJS)
	$(CC) tests/sleep.c -o tests/sleep $(OBJS) $(CFLAGS) $(LDFLAGS) $(LDLIBS)

src/libproc.o: src/libproc.c src/libproc.h
	$(CC) -c $(CFLAGS) src/libproc.c -o src/libproc.o

src/sleep.o: src/sleep.c src/libproc.h
	$(CC) -c $(CFLAGS) src/sleep.c -o src/sleep.o

libproc.so: $(OBJS)
	$(CC) $(OBJS) -shared -o libproc.so
