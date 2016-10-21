#ifndef _CIPHERTEXT_CC
#define _CIPHERTEXT_CC

#define PACK_OPTIMIZATION 1
#define POPCNT_OPTIMIZATION 1

#ifdef POPCNT_OPTIMIZATION
#include <smmintrin.h>
#endif

#include <stdint.h>
#include <stdio.h>

#include "CipherText.h"

ZqMatrix CipherText::operator+(const ZqMatrix& theMat)
{
	CipherText result = ZqMatrix::operator+(theMat);
	return result.flatten();
}

ZqMatrix CipherText::operator-(const ZqMatrix& theMat)
{
	CipherText result = ZqMatrix::operator-(theMat);
	return result.flatten();
}

ZqMatrix CipherText::operator!()
{
	CipherText result = ZqMatrix::operator!();
	return result.flatten();
}

// Left multiplication of this matrix and another
// It is a rectangular matrix or NxN
ZqMatrix CipherText::operator*(const ZqMatrix& theMat)
{
	
        CipherText result(getNumRows(), theMat.getNumCols(), getQ());

	int num = pNumRows;
        int* element = theMat.getElement();

#ifdef PACK_OPTIMIZATION
	// packed matrix
	int wSize = sizeof(uint64_t)*8;
	int packedNum = (num+wSize-1)/wSize;
	uint64_t packedA[num*packedNum];
	uint64_t packedB[num*packedNum];

//	clock_t start = clock();
	pack(packedA, pElement, num, packedNum);
	packTranspose(packedB, element, num, packedNum);
//	clock_t end = clock();

//	printf("pack time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);

        for (int i=0; i<num; i++) {
		uint64_t* a = packedA+i*packedNum;
                for (int j=0; j<num; j++) {
			uint64_t* b = packedB+j*packedNum;
                        int s = 0;
			for(int k=0; k<packedNum; k++) {
				uint64_t t = a[k] & b[k];
#ifdef POPCNT_OPTIMIZATION
				s += _mm_popcnt_u64(t);
#else
				s += countOnes(t);
#endif
			}
//			if(s>pQ) { 
//				printf("s>pQ\n");
//			}
                        result(i,j) = MOD(s,pQ);
		}
	}
#else
        int* a = pElement;
        int* b = element;

        for (int i=0; i<num; i++) {
		int* a = pElement+i*num;
                for (int j=0; j<num; j++) {
			int* b = element+j;
                        int s = 0;
                        for(int k=0; k<num; k++) {
                                s += a[k] & b[num*k];
                        }

                        result(i,j) = MOD(s,pQ);
                }
        }
#endif
	return result.flatten();
}

void CipherText::pack(uint64_t* packMat, int* mat, int num, int packedNum)
{
	int wSize = sizeof(uint64_t)*8;
	for(int i=0; i<num; i++) {
		uint64_t s = 0;
		for(int j=0; j<num; j++) { 
			s = (s<<1) | mat[i*num+j]; 
			if((j+1)%wSize==0) {
				packMat[i*packedNum+j/wSize] = s;
				s = 0;
			}
		}
		packMat[i*packedNum+num/wSize] = s;
	}
}

void CipherText::packTranspose(uint64_t* packMat, int* mat, int num, int packedNum)
{
	int wSize = sizeof(uint64_t)*8;
	for(int j=0; j<num; j++) { 
		uint64_t s = 0;
		for(int i=0; i<num; i++) {
			s = (s<<1) | mat[i*num+j]; 
			if((i+1)%wSize==0) {
				packMat[j*packedNum + i/wSize] = s;
				s = 0;
			}
		}
		packMat[j*packedNum + num/wSize] = s;
	}
}

int CipherText::countOnes(uint64_t v)
{
	int c = 0;
	for(int i=0; i<sizeof(uint64_t)*8; i++) {
		c += v&1;
		v >>= 1;
	}

	return c;
}
		
#endif
