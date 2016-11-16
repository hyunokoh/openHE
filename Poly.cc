#include <stdio.h>
#include "Poly.h"

void Poly::print()
{
	int k;
	for(k=0; k<N; ++k)  {
		printf("%d ", a[k]);
	}
	printf("\n");
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

Poly Poly::operator*(Poly& theA)
{
	Poly ntt0 = ntt(*this, g, N);
	Poly ntt1 = ntt(theA, g, N);

	int k;
	Poly c; 
	for(k=0; k<N; ++k)  {
		c.a[k] = (ntt0.a[k]*ntt1.a[k])%Q;
	}

	return nttInv(c,gInv,N);
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
