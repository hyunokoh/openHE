#
CFLAGS = -w -g -I/usr/local/ssl/include -m64 -march=corei7 -msse4.2
#CFLAGS = -w -o3 -I/usr/local/ssl/include -m64 -march=corei7 -msse4.2

all: Test_rgsw

Test_rgsw : Test_RGSW.cc RGSW.cc RingCipherText.cc RingMatrix.cc Poly.cc
	g++ $(CFLAGS) -DOPTIMIZED -o $@ $^ 

poly : Poly.cc poly_test.cc
	g++ $(CFLAGS) -o $@ $^

clean: 
	rm Test_rgsw
	rm *.o

