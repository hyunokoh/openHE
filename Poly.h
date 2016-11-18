#ifndef _POLY_
#define _POLY_

#include "parameter.h"

// PolyEnv is for optimization
#ifdef OPTIMIZED
class PolyEnv {
public:
	int wn[N];

	PolyEnv(int);
}; 
#endif

class Poly {
private:
       // int a[N];

public:
        int a[N];
	Poly() {}
	Poly(int theInit);

        Poly ntt(Poly& a, int wn, int n);
        Poly nttInv(Poly& a, int wn, int n);
	
	Poly& operator=(const Poly&);

        Poly operator+(Poly&);
        Poly operator-(Poly&);
        Poly operator*(Poly&);

	Poly operator&(int mask);	
	Poly operator>>(int offset);
	Poly operator<<(int offset);

	void randomize();
	void randomizeInX();

	int get(int theDegree) { return a[theDegree]; }

        void print();

#ifdef OPTIMIZED
	// optimized implementation
        void nttOptimized(Poly& y, PolyEnv& env, int startIndex, int n);
        void nttInvOptimized(Poly& y);
#endif
};


#endif
