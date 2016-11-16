
#include "RingMatrix.h"
#include "RingCipherText.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

class RGSW {
protected:
	// private keys
	RingMatrix* pS;

public:
	RGSW();

	void genKeys() { generateSK(); }
	void generateSK();

	RingMatrix generateNewRandom();

	// public key encryption 
	virtual RingCipherText enc(int mu) {return encSec(mu);}

	// In BV14, there are public key based and secret key based encryption
	// secret key encryption
	virtual RingCipherText encSec(int mu);

	// decryption
	virtual int dec(RingCipherText& C,int index=L-1);
	virtual int MPDec(RingCipherText& C, int bitLength, int index = L-1);
};
