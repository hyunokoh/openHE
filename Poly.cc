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

Poly Poly::operator+(Poly& theA)
{
	int k;
	Poly c; 
	for(k=0; k<N; ++k)  {
		c.a[k] = (a[k]+theA.a[k])%Q;
	}

	return c;
}

Poly Poly::operator-(Poly& theA)
{
	int k;
	Poly c; 
	for(k=0; k<N; ++k)  {
		c.a[k] = (a[k]-theA.a[k])%Q;
	}

	return c;
}

Poly Poly::operator*(Poly& theA)
{
#ifdef OPTIMIZED
	Poly ntt0, ntt1;
	this->nttOptimized(ntt0, gPolyEnv, 0, N);
	theA.nttOptimized(ntt1, gPolyEnv, 0, N);
#else
	Poly ntt0 = ntt(*this, g, N);
	Poly ntt1 = ntt(theA, g, N);
#endif

	int k;
	Poly c; 
	for(k=0; k<N; ++k)  {
		c.a[k] = MOD(ntt0.a[k]*ntt1.a[k]);
	}
#ifdef OPTIMIZED
	Poly result;
	c.nttInvOptimized(result);
	return result;
#else
	return nttInv(c,gInv,N);
#endif
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

Poly Poly::ntt(Poly& a, int wn, int n)
{
	int w = 1;
	int k;

	if(n==1) return a;
	
	int wn2 = (wn*wn)%Q;
	Poly a0, a1;
	for(k=0; k<n/2; ++k) {
		a0.a[k] = a.a[2*k];
		a1.a[k] = a.a[2*k+1];
	}

	Poly y0 = ntt(a0, wn2, n/2);
	Poly y1 = ntt(a1, wn2, n/2);

	Poly y;
	for(k=0; k<n/2; ++k) {
		y.a[k] = (y0.a[k] + w*y1.a[k])%Q;	
		y.a[k+n/2] = (y0.a[k] - w*y1.a[k])%Q;	
		w = (w*wn)%Q;	
	}

	return y;
}


Poly Poly::nttInv(Poly& a, int wn, int n)
{
	Poly r = ntt(a, gInv, n);

	Poly y;
	for(int k=0; k<n; ++k) {
		y.a[k] = (r.a[k] * NInv)%Q;	
	}

	return y;
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

#ifdef OPTIMIZED
void Poly::nttOptimized(Poly& y, PolyEnv& env, int startIndex, int n)
{
	int w = 1;
	int k;

	if(n==1) {
		y.a[0] = a[startIndex];
		return;
	}
	
	Poly y0, y1;

	int range = N/n;

	nttOptimized(y0, env, startIndex, n>>1);
	nttOptimized(y1, env, startIndex+range, n>>1);

	for(k=0; k<n/2; ++k) {
		y.a[k] = MOD(y0.a[k] + w*y1.a[k]);	
		y.a[k+n/2] = MOD(y0.a[k] - w*y1.a[k]);	
		w = env.wn[startIndex+k*range];
	}
}

void Poly::nttInvOptimized(Poly& y)
{
	nttOptimized(y, gPolyInvEnv, 0, N);

	for(int k=0; k<N; ++k) {
		y.a[k] = MOD(y.a[k] * NInv);	
	}
}
#endif
