

#include "ZqMatrix.h"
#include "CipherText.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


//const int l = 3;
//const int n = 3;	// Note that to support *, at least, N < 2^{l-2}/2
const int l = 20;
const int n = 80;	// Note that to support *, at least, N < 2^{l-2}/2
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

	void setup();

	int getZq();

	int getX();

	void generateSK();
	void generatePK();

	ZqMatrix generateNewRandom();

	void genKeys();

	// public key encryption 
	ZqMatrix enc(int mu);

	// In BV14, there are public key based and secret key based encryption
	// secret key encryption
	ZqMatrix encSec(int mu);

	// decryption
	int dec(ZqMatrix& C,int index=l-1);
	int MPDec(ZqMatrix& C, int bitLength, int index = l-1);
};
