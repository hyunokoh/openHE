#ifndef _POLY_
#define _POLY_

#include "parameter.h"

// PolyEnv is for optimization
class PolyEnv {
public:
	int wn[N];

	PolyEnv(int);
}; 

class Poly {
private:
        int a[N];

public:
	Poly() {}
	Poly(int theInit);

	void ntt(Poly& y);
        void nttInv(Poly& y);

        void ntt(Poly& y, PolyEnv& env, int startIndex, int n);
	
	Poly& operator=(const Poly&);

        //Poly operator+(Poly&);
        //Poly operator-(Poly&);
        //Poly operator*(Poly&);

	friend void add(Poly& theC, Poly& theA, Poly& theB);
	friend void sub(Poly& theC, Poly& theA, Poly& theB);
	friend void mul(Poly& theC, Poly& theA, Poly& theB);

	Poly operator&(int mask);	
	Poly operator>>(int offset);
	Poly operator<<(int offset);

	void randomize();
	void randomizeInX();

	int get(int theDegree) { return a[theDegree]; }

        void print();
};


#endif
