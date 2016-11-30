#include <stdint.h>
#include <stdio.h>

#include "RingCipherText.h"

// Left multiplication of this matrix and another
// It is a rectangular matrix or NxN
RingMatrix RingCipherText::operator*(const RingMatrix& theMat)
{
	RingMatrix d = bitDecomp();
	RingMatrix e(theMat.getNumRows(), theMat.getNumCols());
	d.ntt(d);
	theMat.ntt(e);
	RingMatrix t = d*e;
	t.nttInv(t);

	return t;
}

void mulCipherText(RingCipherText& theC, RingMatrix& theA, RingMatrix& theB)
{
	RingMatrix d(theA.getNumRows(), theA.getNumCols()*L);
	RingMatrix e(theB.getNumRows(), theB.getNumCols());
	theA.decompose(d);
	d.ntt(d);
	theB.ntt(e);
	mulMat(theC, d, e);
	theC.nttInv(theC);
}
