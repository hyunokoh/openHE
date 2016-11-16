#
CFLAGS = -w -g -I/usr/local/ssl/include -m64 -march=corei7 -msse4.2
#CFLAGS = -w -o3 -I/usr/local/ssl/include -m64 -march=corei7 -msse4.2

all: Test_basic Test_adder gsw poly

gsw: gsw.cc ZqMatrix.cc CipherText.cc
	g++ $(CFLAGS) -o $@ $^ 

Test_basic : Test_basic.cc FHE.cc CipherText.cc APCipherText.cc ZqMatrix.cc
	g++ $(CFLAGS) -o $@ $^ 

Test_adder : Test_adder.cc FHE.cc CipherText.cc ZqMatrix.cc
	g++ $(CFLAGS) -o $@ $^ 

poly : Poly.cc poly_test.cc
	g++ $(CFLAGS) -o $@ $^ 

clean: 
	rm gsw Test_basic Test_adder poly
	rm *.o

