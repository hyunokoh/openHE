#ifndef __Zq_MATRIX_H
#define __Zq_MATRIX_H

//Optimized for GSW. q = power of 2

#include <vector>

#define MOD(x,q) ((x) & ((q)-1))

class ZqMatrix {
protected:
	int* pElement;
	int pNumRows;
	int pNumCols;
	int pQ; 	// modulus Q
	int pL;
  
public:
	ZqMatrix();
	ZqMatrix(int theNumRows, int theNumCols, int theQ); 
	ZqMatrix(const ZqMatrix& theMat);
	virtual ~ZqMatrix();

	// Operator overloading, for "standard" mathematical matrix operations 
	ZqMatrix& operator=(const ZqMatrix& theMat);

	// Matrix mathematical operations
	virtual ZqMatrix operator+(const ZqMatrix& theMat);
	virtual ZqMatrix operator-(const ZqMatrix& theMat);
	virtual ZqMatrix operator*(const ZqMatrix& theMat);
	virtual ZqMatrix operator!();

	// Access the individual elements                               
	int& operator()(const int& row, const int& col) { return pElement[row*pNumCols+col]; }
	const int& operator()(const int& row, const int& col) const { return pElement[row*pNumCols+col]; }

	// GSW related functions
	static ZqMatrix identity(int theNumRows, int theInitValue=1,int theQ=1, int theL=1);

	void randomize(int range);

	ZqMatrix flatten();
	ZqMatrix bitDecomp();
	ZqMatrix invBitDecomp();

	ZqMatrix getRowVector(int theRow); 

	// Access elements
	int* getElement() const { return pElement; }

	// Access the row and column sizes                              
	int getNumRows() const { return pNumRows; }
	int getNumCols() const { return pNumCols; }
	int getQ() const { return pQ; }
	int getL() const { return pL; }

	// setup parameters
	void setQ(int theQ) { pQ = theQ; }
	void setL(int theL) { pL = theL; }
};

#endif

