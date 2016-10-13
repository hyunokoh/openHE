#
CFLAGS = -w -g -I/usr/local/ssl/include -m64 -march=corei7 -msse4.2

all: Test_basic Test_adder gsw

gsw: gsw.cc ZqMatrix.cc CipherText.cc
	g++ $(CFLAGS) -o $@ $^ 

Test_basic : Test_basic.cc FHE.cc CipherText.cc ZqMatrix.cc
	g++ $(CFLAGS) -o $@ $^ 

Test_adder : Test_adder.cc FHE.cc CipherText.cc ZqMatrix.cc
	g++ $(CFLAGS) -o $@ $^ 

clean: 
	rm gsw
	rm *.o

