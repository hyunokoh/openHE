#ifndef _RING_CIPHERTEXT_H
#define _RING_CIPHERTEXT_H

#include <stdint.h>

#include "RingMatrix.h"

class RingCipherText : public RingMatrix 
{
public:
        RingCipherText(){}
        RingCipherText(int theNumRows, int theNumCols) : RingMatrix(theNumRows, theNumCols){}
        RingCipherText(const RingMatrix& theMat) : RingMatrix(theMat){}
        virtual ~RingCipherText(){}

        /*virtual*/ RingMatrix operator*(const RingMatrix& theMat);
	friend void mulCipherText(RingCipherText&, RingMatrix&, RingMatrix&);
};

#endif
