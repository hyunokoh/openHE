

#include "ZqMatrix.h"
#include "CipherText.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


//const int l = 20;
//const int n = 80;	// Note that to support *, at least, N < 2^{l-2}/2
const int l = 30;
const int n = 10;	// Note that to support *, at least, N < 2^{l-2}/2
const int q = (1<<(l));
//const int m = (2*n*l);
const int m = (n+1)*(l+3);	// In BV14, m = (n+1)(l+O(1))
const int N = (n+1)*l; 

//ZqMatrix s(n+1,1,q);
//ZqMatrix v(N,1,q);
//ZqMatrix A(m,n+1,q);
//ZqMatrix t(n,1,q);

class FHE {
protected:
	// private keys
	ZqMatrix* pS, *pV;

	// public keys
	ZqMatrix* pA;

	// temporary secret parameter
	ZqMatrix* pT;
public:
	FHE();

	virtual void setup();

	int getZq();

	int getX();

	virtual void generateSK();
	virtual void generatePK();

	ZqMatrix generateNewRandom();

	virtual void genKeys();

	// public key encryption 
	virtual ZqMatrix enc(int mu);

	// In BV14, there are public key based and secret key based encryption
	// secret key encryption
	virtual ZqMatrix encSec(int mu);

	// decryption
	virtual int dec(ZqMatrix& C,int index=l-1);
	virtual int MPDec(ZqMatrix& C, int bitLength, int index = l-1);
};
