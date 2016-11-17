#include <stdint.h>
#include <stdio.h>

#include "RingCipherText.h"

// Left multiplication of this matrix and another
// It is a rectangular matrix or NxN
RingMatrix RingCipherText::operator*(const RingMatrix& theMat)
{
	RingMatrix t = *this;
	t.nttInv();
	RingMatrix d = t.bitDecomp();
	d.ntt();
	return d*theMat;
}
