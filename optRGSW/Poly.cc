#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Poly.h"

#ifdef OPTIMIZED
PolyEnv::PolyEnv(int theG)
{
	wn[0] = 1;
	for(int k=1; k<N; ++k) {
		wn[k] = MOD(wn[k-1]*theG); 
	}
}

PolyEnv gPolyEnv(g);
PolyEnv gPolyInvEnv(gInv);
#endif

Poly::Poly(int theInit)
{
	int k;
	for(k=1; k<N; ++k)  {
		a[k] = 0;
	}
	a[0] = theInit;
}

void Poly::print()
{
	int k;
	for(k=0; k<N; ++k)  {
		printf("%d ", a[k]);
	}
	printf("\n");
}

Poly& Poly::operator=(const Poly& theA)
{
	int k;
	for(k=0; k<N; ++k)  {
		a[k] = theA.a[k];
	}

	return *this;
}

void add(Poly& theC, Poly& theA, Poly& theB)
{
	int k;
	for(k=0; k<N; ++k)  {
		theC.a[k] = MOD(theA.a[k]+theB.a[k]);
	}
}

void sub(Poly& theC, Poly& theA, Poly& theB)
{
	int k;
	for(k=0; k<N; ++k)  {
		theC.a[k] = MOD(theA.a[k]-theB.a[k]);
	}
}

void mul(Poly& theC, Poly& theA, Poly& theB)
{
//	Poly ntt0, ntt1;
//	this->ntt(ntt0, gPolyEnv, 0, N);
//	theA.ntt(ntt1, gPolyEnv, 0, N);

	int k;
	for(k=0; k<N; ++k)  {
		theC.a[k] = MOD(theA.a[k]*theB.a[k]);
	}
}

Poly Poly::operator&(int mask)
{
	int k;
	Poly c; 
	for(k=0; k<N; ++k)  {
		c.a[k] = a[k] & mask; 
	}

	return c;
}

Poly Poly::operator>>(int offset)
{
	int k;
	Poly c; 
	for(k=0; k<N; ++k)  {
		c.a[k] = a[k] >> offset;
	}

	return c;
}

Poly Poly::operator<<(int offset)
{
	int k;
	Poly c; 
	for(k=0; k<N; ++k)  {
		c.a[k] = a[k] << offset;
	}

	return c;
}

void Poly::randomize()
{
	int k;
	for(k=0; k<N; ++k)  {
		a[k] = rand()%Q;
	}
}

void Poly::randomizeInX()
{
	int k;
	for(k=0; k<N; ++k)  {
		a[k] = (rand()%3) - 1;
	}
}

void Poly::ntt(Poly& y, PolyEnv& env, int startIndex, int n)
{
	int w = 1;
	int k;

	if(n==1) {
		y.a[0] = a[startIndex];
		return;
	}
	
	Poly y0, y1;

	int range = N/n;

	ntt(y0, env, startIndex, n>>1);
	ntt(y1, env, startIndex+range, n>>1);

	for(k=0; k<n/2; ++k) {
		y.a[k] = MOD(y0.a[k] + w*y1.a[k]);	
		y.a[k+n/2] = MOD(y0.a[k] - w*y1.a[k]);	
		w = env.wn[startIndex+k*range];
	}
}

void Poly::nttInv(Poly& y)
{
	ntt(y, gPolyInvEnv, 0, N);

	for(int k=0; k<N; ++k) {
		y.a[k] = MOD(y.a[k] * NInv);	
	}
}
