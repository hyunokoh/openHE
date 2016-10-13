#ifndef _CIPHERTEXT_H
#define _CIPHERTEXT_H

#include <stdint.h>

#include "ZqMatrix.h"

class CipherText : public ZqMatrix 
{
public:
        CipherText(){}
        CipherText(int theNumRows, int theNumCols, int theQ) : ZqMatrix(theNumRows, theNumCols, theQ){}
        CipherText(const ZqMatrix& theMat) : ZqMatrix(theMat){}
        virtual ~CipherText(){}

	/*virtual*/ ZqMatrix operator+(const ZqMatrix& theMat);
        /*virtual*/ ZqMatrix operator-(const ZqMatrix& theMat);
        /*virtual*/ ZqMatrix operator*(const ZqMatrix& theMat);

	void pack(uint64_t* packMat, int* mat, int numRows, int numCols);
	void packTranspose(uint64_t* packMat, int* mat, int numRows, int numCols);

	int countOnes(uint64_t v);
};

#endif
