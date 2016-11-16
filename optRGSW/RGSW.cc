#include "RGSW.h"
#include "RingCipherText.h"
#include <stdlib.h>
#include <stdio.h>

RGSW::RGSW()
{
	pS = new RingMatrix(2,1);
}

void RGSW::generateSK()
{
	(*pS)(0,0) = Poly(1);
	(*pS)(1,0).randomize();
}

RingMatrix RGSW::generateNewRandom()
{
	int i,j;
	RingMatrix r(2*L,2);
	Poly e;
	for(i=0; i<2*L; i++) {
		r(i,1).randomize();
		e.randomizeInX();

		mul(r(i,0), r(i,1), (*pS)(1,0));
		sub(r(i,0), e, r(i,0));
	}

	return r;
}

// In BV14, there are public key based and secret key based encryption
RingCipherText RGSW::encSec(int mu)
{
	if(mu) {
		return generateNewRandom()+RingMatrix::identity(2*L, mu).invBitDecomp();
	} else {
		return generateNewRandom();
	}
}

int RGSW::dec(RingCipherText& C,int index)
{
	RingMatrix C_i = C.getRowVector(index);

	RingMatrix  x_i = C_i * (*pS);

	// we compute \lfloor x_i / v_i \rceil. 
	// If v_i/2 < x_i <= 3v_i/2 then it is 1, otherwise it is 0.
	int v_i = 1<<index;

	int t = (x_i(0,0).get(0)+v_i/2) / v_i;

	return t&1;
}

int RGSW::MPDec(RingCipherText& C, int bitLength, int index)
{
	int i = index-bitLength+1;
	int mu=0;
	RingMatrix C_i = C.getRowVector(i);
        RingMatrix  x_i = C_i * (*pS);
	int v_i = 1<<i;
	int t = (x_i(0,0).get(0)+v_i/2) / v_i;
	mu = (t&((1<<bitLength)-1));

	return mu;			
}
