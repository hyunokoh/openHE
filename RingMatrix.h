#ifndef __Ring_MATRIX_H
#define __Ring_MATRIX_H

//Optimized for GSW. 

#include "Poly.h"

class RingMatrix {
protected:
	Poly* pElement;
	int pNumRows;
	int pNumCols;
  
public:
	RingMatrix();
	RingMatrix(int theNumRows, int theNumCols); 
	RingMatrix(const RingMatrix& theMat);
	virtual ~RingMatrix();

	// Operator overloading, for "standard" mathematical matrix operations 
	RingMatrix& operator=(const RingMatrix& theMat);

	// Matrix mathematical operations
	virtual RingMatrix operator+(const RingMatrix& theMat);
	virtual RingMatrix operator-(const RingMatrix& theMat);
	virtual RingMatrix operator*(const RingMatrix& theMat);
	virtual RingMatrix operator!();

	// Access the individual elements                               
	Poly& operator()(const int& row, const int& col) { return pElement[row*pNumCols+col]; }
	const Poly& operator()(const int& row, const int& col) const { return pElement[row*pNumCols+col]; }

	// Ring GSW related functions
	static RingMatrix identity(int theNumRows, int theInitValue=1);

	RingMatrix bitDecomp();
	RingMatrix invBitDecomp();

	RingMatrix getRowVector(int theRow); 

	// Access elements
	Poly* getElement() const { return pElement; }

	// Access the row and column sizes                              
	int getNumRows() const { return pNumRows; }
	int getNumCols() const { return pNumCols; }
};

#endif

