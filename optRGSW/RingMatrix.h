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

	friend void mul(RingMatrix& theC, const RingMatrix& theA, const RingMatrix& theB);
	friend void mulMat(RingMatrix& theC, const RingMatrix& theA, const RingMatrix& theB) { mul(theC, theA, theB); }

	// for each item, apply ntt or nttInv
	void ntt(RingMatrix&) const;
	void nttInv(RingMatrix&) const;

	// Access the individual elements                               
	Poly& operator()(const int& row, const int& col) { return pElement[row*pNumCols+col]; }
	const Poly& operator()(const int& row, const int& col) const { return pElement[row*pNumCols+col]; }

	// Ring GSW related functions
	static RingMatrix identity(int theNumRows, int theInitValue=1);

	RingMatrix bitDecomp();
	RingMatrix invBitDecomp();

	void decompose(RingMatrix& result);
	void compose(RingMatrix& result);

	RingMatrix getRowVector(int theRow); 

	// Access elements
	Poly* getElement() const { return pElement; }
	Poly& getElement(int index) const { return pElement[index]; }
	void setElement(int index, Poly& p) { pElement[index] =  p; }

	// Access the row and column sizes                              
	int getNumRows() const { return pNumRows; }
	int getNumCols() const { return pNumCols; }
};

#endif

