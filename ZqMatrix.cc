#ifndef __Zq_MATRIX_CPP
#define __Zq_MATRIX_CPP

#include <stdlib.h>
#include <math.h>
#include "ZqMatrix.h"

ZqMatrix::ZqMatrix() { }

ZqMatrix::ZqMatrix(int theNumRows, int theNumCols, int theQ) {
	pNumRows = theNumRows;
	pNumCols = theNumCols;
	pQ = theQ;

	pElement = new int[pNumRows*pNumCols];
	//memset(pElement,0, pNumRows*pNumCols*sizeof(int));


	for(int i=0; i<32; i++) {
		if((pQ>>i) == 1) {
			pL = i;
			break;
		}
	}
}

ZqMatrix::ZqMatrix(const ZqMatrix& theMat) {
	pNumRows = theMat.getNumRows();
	pNumCols = theMat.getNumCols();
	pQ = theMat.getQ();
	pL = theMat.getL();
	pElement = theMat.pElement;
}

ZqMatrix::~ZqMatrix() {}

// Assignment Operator
ZqMatrix& ZqMatrix::operator=(const ZqMatrix& theMat) {
	if (&theMat == this)
		return *this;

	pNumRows = theMat.getNumRows();
	pNumCols = theMat.getNumCols();
	pQ = theMat.getQ();
	pL = theMat.getL();

	pElement = theMat.getElement();

/*
	pElement = new int[pNumRows*pNumCols];
	//memset(pElement,0, pNumRows*pNumCols*sizeof(int));

	for (int i=0; i<pNumRows; i++) {
		for (int j=0; j<pNumCols; j++) {
			(*this)(i,j) = theMat(i, j);
		}
	}
*/
	return *this;
}

// Addition of two matrices
ZqMatrix ZqMatrix::operator+(const ZqMatrix& theMat) 
{
	ZqMatrix result(pNumRows, pNumCols, pQ);
	int* a = result.getElement();
	int* b = theMat.getElement();

	for (int i=0; i<pNumRows*pNumCols; i++) {
		a[i] = MOD(pElement[i]+b[i],pQ);
	}

	return result;
}

// Substraction of two matrices
ZqMatrix ZqMatrix::operator-(const ZqMatrix& theMat) 
{
	ZqMatrix result(pNumRows, pNumCols, pQ);
	int* a = result.getElement();
	int* b = theMat.getElement();

	for (int i=0; i<pNumRows*pNumCols; i++) {
		a[i] = MOD(pElement[i]-b[i]+pQ,pQ);
	}

	return result;
}

// Left multiplication of this matrix and another
ZqMatrix ZqMatrix::operator*(const ZqMatrix& theMat) 
{
	ZqMatrix result(pNumRows, theMat.getNumCols(), pQ);
	int numCols = theMat.getNumCols();
	int* element = theMat.getElement();

	for (int i=0; i<pNumRows; i++) {
		int* a = pElement+i*pNumCols;
		for (int j=0; j<numCols; j++) {
			int* b = element+j;
			int s = 0;
			for(int k=0; k<pNumCols; k++) { 
        			s += a[k] * b[numCols*k];
			}
//			if(s>pQ) {
//				printf("mul : s>pQ : %d\n", s);
//			}
        		result(i,j) = MOD(s,pQ);
		}
	}

	return result;
}

ZqMatrix ZqMatrix::identity(int theNumRows, int theInitValue)
{
	ZqMatrix result(theNumRows, theNumRows, 1);
	for (int i=0; i<theNumRows; i++) {
		for(int j=0; j<theNumRows; j++) {
			if(i==j) result(i,i) = theInitValue;
			else	result(i,j) = 0;
		}
	}

	return result;
}


 
void ZqMatrix::randomize(int theRange)
{
	for (int i=0; i<pNumRows; i++) {
		for (int j=0; j<pNumCols; j++) {
			(*this)(i,j) = rand() % theRange;
		}
	}
}

ZqMatrix ZqMatrix::flatten()
{
	ZqMatrix result1 = invBitDecomp();
	return result1.bitDecomp();
}

ZqMatrix ZqMatrix::bitDecomp()
{
	ZqMatrix result(pNumRows, pNumCols*pL, pQ);
	int* a = result.getElement();

	for (int i=0; i<pNumRows; i++) {
		for (int j=0; j<pNumCols; j++) {
			int x = pElement[i*pNumCols+j];
			int* e = a+i*pNumCols*pL+j*pL;
			for (int k=0; k<pL; k++) {
				e[k] = x & 1;
				x = x>>1;
			}
		}
	}

	return result;
}

ZqMatrix ZqMatrix::invBitDecomp()
{
	ZqMatrix result(pNumRows, pNumCols/pL, pQ);
	int* e = pElement;
	int* a = result.getElement();

	for (int i=0; i<pNumRows; i++) {
		for (int j=0; j<pNumCols/pL; j++) {
			int x=0;
			e = pElement + i*pNumCols+j*pL;
			for(int k=0; k<pL; k++) {
				x = x + (e[k]<<k);
			}
			a[i*pNumCols/pL+j] = x;
		}
	}

	return result;
}

ZqMatrix ZqMatrix::getRowVector(int theRow)
{
	ZqMatrix result(1, pNumCols, pQ);

	for (int j=0; j<pNumCols; j++) {
		result(0,j) = (*this)(theRow,j);
	}

	return result;
}
#endif
