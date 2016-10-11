#define PACK_OPTIMIZATION 1
#define POPCNT_OPTIMIZATION 1

#ifdef POPCNT_OPTIMIZATION
#include <smmintrin.h>
#endif

#include "ZqMatrix.h"

class CipherText : public ZqMatrix 
{
public:
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

ZqMatrix CipherText::operator+(const ZqMatrix& theMat)
{
	CipherText result = ZqMatrix::operator+(theMat);
	result.flatten();
        return result;
}

ZqMatrix CipherText::operator-(const ZqMatrix& theMat)
{
	CipherText result = ZqMatrix::operator-(theMat);
	result.flatten();
        return result;
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

	clock_t start = clock();
	pack(packedA, element, num, packedNum);
	packTranspose(packedB, element, num, packedNum);
	clock_t end = clock();

	printf("pack time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);

        for (int i=0; i<num; i++) {
		uint64_t* a = packedA+i*packedNum;
                for (int j=0; j<num; j++) {
			uint64_t* b = packedB+j*packedNum;
                        int s = 0;
			for(int k=0; k<packedNum; k++) {
				int t = packedA[k] & packedB[k];
#ifdef POPCNT_OPTIMIZATION
				s += _mm_popcnt_u64(t);
#else
				s += countOnes(t);
#endif
			}
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
	result.flatten();
        return result;
}

void CipherText::pack(uint64_t* packMat, int* mat, int num, int packedNum)
{
	int wSize = sizeof(uint64_t)*8;
	for(int i=0; i<num; i++) {
		int s = 0;
		for(int j=0; j<num; j++) { 
			s = (s<<1) | mat[i*num+j]; 
			if((j+1)%wSize==0) {
				packMat[i*packedNum+j/wSize] = s;
				s = 0;
			}
		}
	}
}

void CipherText::packTranspose(uint64_t* packMat, int* mat, int num, int packedNum)
{
	int wSize = sizeof(uint64_t)*8;
	for(int j=0; j<num; j++) { 
		int s = 0;
		for(int i=0; i<num; i++) {
			s = (s<<1) | mat[i*num+j]; 
			if((i+1)%wSize==0) {
				packMat[j*packedNum + i/wSize] = s;
				s = 0;
			}
		}
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
		

