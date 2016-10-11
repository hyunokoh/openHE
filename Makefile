#
CFLAGS = -w -g -I/usr/local/ssl/include -m64 -march=corei7 -msse4.2

all: gsw

gsw: gsw.cc ZqMatrix.cc
	g++ $(CFLAGS) -o $@ $^ 

clean: 
	rm gsw
	rm *.o

