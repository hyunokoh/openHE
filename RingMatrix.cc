#ifndef __Ring_MATRIX_CPP
#define __Ring_MATRIX_CPP

#include <stdlib.h>
#include <math.h>
#include "RingMatrix.h"

RingMatrix::RingMatrix() { }

RingMatrix::RingMatrix(int theNumRows, int theNumCols) {
	pNumRows = theNumRows;
	pNumCols = theNumCols;

	pElement = new Poly[pNumRows*pNumCols];
}

RingMatrix::RingMatrix(const RingMatrix& theMat) {
	pNumRows = theMat.getNumRows();
	pNumCols = theMat.getNumCols();
	pElement = theMat.pElement;
}

RingMatrix::~RingMatrix() {}

// Assignment Operator
RingMatrix& RingMatrix::operator=(const RingMatrix& theMat) {
	if (&theMat == this)
		return *this;

	pNumRows = theMat.getNumRows();
	pNumCols = theMat.getNumCols();

	pElement = theMat.getElement();

	return *this;
}

// Addition of two matrices
RingMatrix RingMatrix::operator+(const RingMatrix& theMat) 
{
	RingMatrix result(pNumRows, pNumCols);
	Poly* a = result.getElement();
	Poly* b = theMat.getElement();

	for (int i=0; i<pNumRows*pNumCols; i++) {
		a[i] = pElement[i]+b[i];
	}

	return result;
}

// Substraction of two matrices
RingMatrix RingMatrix::operator-(const RingMatrix& theMat) 
{
	RingMatrix result(pNumRows, pNumCols);
	Poly* a = result.getElement();
	Poly* b = theMat.getElement();

	for (int i=0; i<pNumRows*pNumCols; i++) {
		a[i] = pElement[i]-b[i];
	}

	return result;
}

RingMatrix RingMatrix::operator!()
{
	RingMatrix result(pNumRows, pNumCols);

	result = identity(pNumRows,1) - *this;
 
	return result;
}

// Left multiplication of this matrix and another
RingMatrix RingMatrix::operator*(const RingMatrix& theMat) 
{
	RingMatrix result(pNumRows, theMat.getNumCols());
	int numCols = theMat.getNumCols();
	Poly* element = theMat.getElement();

	for (int i=0; i<pNumRows; i++) {
		Poly* a = pElement+i*pNumCols;
		for (int j=0; j<numCols; j++) {
			Poly* b = element+j;
			Poly s(0);
			for(int k=0; k<pNumCols; k++) { 
        			s = a[k] * b[numCols*k] + s;
			}
        		result(i,j) = s;
		}
	}

	return result;
}

RingMatrix RingMatrix::identity(int theNumRows, int theInitValue)
{
	RingMatrix result(theNumRows, theNumRows);
	for (int i=0; i<theNumRows; i++) {
		for(int j=0; j<theNumRows; j++) {
			if(i==j) result(i,i) = Poly(theInitValue);
			else	result(i,j) = 0;
		}
	}

	return result;
}

RingMatrix RingMatrix::bitDecomp()
{
	RingMatrix result(pNumRows, pNumCols*L);
	Poly* a = result.getElement();

	for (int i=0; i<pNumRows; i++) {
		for (int j=0; j<pNumCols; j++) {
			Poly x = pElement[i*pNumCols+j];
			Poly* e = a+i*pNumCols*L+j*L;
			for (int k=0; k<L; k++) {
				e[k] = x & 1;
				x = x>>1;
			}
		}
	}

	return result;
}

RingMatrix RingMatrix::invBitDecomp()
{
	RingMatrix result(pNumRows, pNumCols/L);
	Poly* e = pElement;
	Poly* a = result.getElement();

	for (int i=0; i<pNumRows; i++) {
		for (int j=0; j<pNumCols/L; j++) {
			Poly x(0);
			e = pElement + i*pNumCols+j*L;
			for(int k=0; k<L; k++) {
				x = (e[k]<<k) + x;
			}
			a[i*pNumCols/L+j] = x;
		}
	}

	return result;
}

RingMatrix RingMatrix::getRowVector(int theRow)
{
	RingMatrix result(1, pNumCols);

	for (int j=0; j<pNumCols; j++) {
		result(0,j) = (*this)(theRow,j);
	}

	return result;
}

#endif
