#include "FHE.h"
#include "CipherText.h"
#include <stdlib.h>
#include <stdio.h>

FHE::FHE()
{
	pS = new ZqMatrix(n+1,1,q);
	pV = new ZqMatrix(N,1,q);
	pA = new ZqMatrix(m,n+1,q);
	pT = new ZqMatrix(n,1,q);
}

void FHE::setup()
{
}

int FHE::getZq()
{
	return rand()%q;
}

int FHE::getX()
{
	//return 0;
	return (rand()%3)-1;
}

void FHE::generateSK()
{
	(*pS)(0,0) = 1;
	int i, j;
	for(i=0; i<n;i++) {
		(*pT)(i,0) = getZq();
		(*pS)(i+1,0) = MOD(q-(*pT)(i,0),q);

	}
	for(i=0; i<n+1; i++)
		for(j=0; j<l; j++)
			(*pV)(i*l+j, 0) = MOD(((*pS)(i,0)* (1<<j)),q);
}

void FHE::generatePK()
{
	int i,j;
	// B <-- Z^{m*n}_q
	ZqMatrix B(m,n,q), e(m,1,q);
	for(i=0; i<m; i++) {
		for(j=0; j<n; j++) {
			B(i,j) = getZq();
		}	
		e(i,0) = getX();
	}

	ZqMatrix b = B * (*pT)+e;
	for(i=0;i<m; i++) {
		(*pA)(i,0) = b(i,0);
		for(j=0; j<n; j++) {
			(*pA)(i,j+1) = B(i,j);
		}
	}
}

ZqMatrix FHE::generateNewRandom()
{
	int i,j;
	// R <-- Z^{N*n}_q
	ZqMatrix R(N,n,q), e(N,1,q);
	for(i=0; i<N; i++) {
		for(j=0; j<n; j++) {
			R(i,j) = getZq();
		}	
		e(i,0) = getX();
	}

	ZqMatrix b = R * (*pT)+e;
	ZqMatrix r(N,N,q);
	for(i=0;i<N; i++) {
		r(i,0) = b(i,0);
		for(j=0; j<n; j++) {
			r(i,j+1) = R(i,j);
		}
	}

	return r;
}

void FHE::genKeys()
{
	// generate sk
	generateSK();

	// generate pk
	generatePK();
}

ZqMatrix FHE::enc(int mu)
{
//	clock_t start,end;
	ZqMatrix R(N,m,q);
	R.randomize(2);

//	start = clock();
	ZqMatrix c = R * (*pA);
//	end = clock();
//	printf("c mul time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);
	c = c.bitDecomp(); 

	if(mu) {
		c = c+ZqMatrix::identity(N, mu);
		
		return c.flatten();
	} else {
		return c;
	}
}

// In BV14, there are public key based and secret key based encryption
ZqMatrix FHE::encSec(int mu)
{
//	clock_t start,end;

//	start = clock();
	ZqMatrix c = generateNewRandom().bitDecomp();
//	end = clock();
//	printf("c mul time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);

	if(mu) {
		c = c+ZqMatrix::identity(N, mu);
		
		return c.flatten();
	} else {
		return c;
	}
}

int FHE::dec(ZqMatrix& C,int index)
{
	ZqMatrix C_i = C.getRowVector(index);

	ZqMatrix  x_i = C_i * (*pV);

	// we compute \lfloor x_i / v_i \rceil. 
	// If v_i/2 < x_i <= 3v_i/2 then it is 1, otherwise it is 0.
	int v_i = 1<<index;

	int t = (x_i(0,0)+v_i/2) / v_i;

	return t&1;
}

int FHE::MPDec(ZqMatrix& C, int bitLength, int index)
{
	int i = index-bitLength+1;
	int mu=0;
	ZqMatrix C_i = C.getRowVector(i);
        ZqMatrix  x_i = C_i * (*pV);
	int v_i = 1<<i;
	int t = (x_i(0,0)+v_i/2) / v_i;
	mu = (t&((1<<bitLength)-1));

	return mu;			
}
