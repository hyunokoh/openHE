#include "ZqMatrix.h"
#include "CipherText.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


const int l = 8;
const int n = 8;	// Note that to support *, at least, N < 2^{l-2}/2
//const int l = 20;
//const int n = 80;	// Note that to support *, at least, N < 2^{l-2}/2
const int q = (1<<(l));
//const int m = (2*n*l);
const int m = (n+1)*(l+3);	// In BV14, m = (n+1)(l+O(1))
const int N = (n+1)*l; 

/*
const int q = 128;
const int l = 7;
//const int q = 23;
//const int l = 5;
const int n = 2;
const int m = 3;	// m = n+1;
const int N = m*l; 
*/

// private keys
ZqMatrix s(n+1,1,q);
ZqMatrix v(N,1,q);

// public keys
ZqMatrix A(m,n+1,q);


// the following are temporary variables. They will be moved into their functions. Currently they are moved out to the global area for debugging purpose.
//ZqMatrix B(m,n,q), e(m,1,q);
ZqMatrix t(n,1,q);
ZqMatrix b(m,1,q);
ZqMatrix R(N,m,q);
void setup()
{
}

int getZq()
{
	return rand()%q;
}

int getX()
{
	return 0;
	//return (rand()%3)-1;
}

void generateSK()
{
	s(0,0) = 1;
	int i, j;
	for(i=0; i<n;i++) {
		t(i,0) = getZq();
		s(i+1,0) = MOD(q-t(i,0),q);

	}
	for(i=0; i<n+1; i++)
		for(j=0; j<l; j++)
			v(i*l+j, 0) = MOD((s(i,0)* (1<<j)),q);
}

void generatePK()
{
	int i,j;
	// B <-- Z^{m*n}_q
	ZqMatrix B(m,n,q), e(m,1,q);
	for(i=0; i<m; i++) {
		for(j=0; j<n; j++) {
			B(i,j) = getZq();
		}	
		e(i,0) = getX();
	}

	//ZqMatrix b(m,1,q);
	//ZqMatrix b = B*t+e;
	b = B*t+e;

	for(i=0;i<m; i++) {
		A(i,0) = b(i,0);
		for(j=0; j<n; j++) {
			A(i,j+1) = B(i,j);
		}
	}
}

ZqMatrix generateNewRandom()
{
	int i,j;
	// R <-- Z^{N*n}_q
	ZqMatrix R(N,n,q), e(N,1,q);
	for(i=0; i<N; i++) {
		for(j=0; j<n; j++) {
			R(i,j) = getZq();
		}	
		e(i,0) = getX();
	}

	ZqMatrix b = R*t+e;
	ZqMatrix r(N,N,q);
	for(i=0;i<N; i++) {
		r(i,0) = b(i,0);
		for(j=0; j<n; j++) {
			r(i,j+1) = R(i,j);
		}
	}

	return r;
}

void genKeys()
{
	// generate sk
	generateSK();

	// generate pk
	generatePK();
}

ZqMatrix enc(int mu)
{
	clock_t start,end;
	//ZqMatrix R(N,m,q);
	R.randomize(2);

	start = clock();
	ZqMatrix c = R*A;
	end = clock();
	printf("c mul time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);
	c = c.bitDecomp(); 

	if(mu) {
		c = c+ZqMatrix::identity(N, mu);
		
		return c.flatten();
	} else {
		return c;
	}
}

// In BV14, there are public key based and secret key based encryption
ZqMatrix encSec(int mu)
{
	clock_t start,end;

	start = clock();
	ZqMatrix c = generateNewRandom().bitDecomp();
	end = clock();
	printf("c mul time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);

	if(mu) {
		c = c+ZqMatrix::identity(N, mu);
		
		return c.flatten();
	} else {
		return c;
	}
}

int dec(ZqMatrix& C,int index=l-1)
{
	ZqMatrix C_i = C.getRowVector(index);

	ZqMatrix  x_i = C_i * v;

	// we compute \lfloor x_i / v_i \rceil. 
	// If v_i/2 < x_i <= 3v_i/2 then it is 1, otherwise it is 0.
	int v_i = 1<<index;
	//float t = 2.0*(x_i(0,0))/v_i;
	//if(t>1.0 && t<=3.0) return 1;
	//else return 0;

	int t = (x_i(0,0)+v_i/2) / v_i;

	return t&1;
}

int MPDec(ZqMatrix& C, int bitLength, int index = l-1)
{
	int i = index-bitLength+1;
	int mu=0;
	ZqMatrix C_i = C.getRowVector(i);
        ZqMatrix  x_i = C_i * v;
	int v_i = 1<<i;
	int t = (x_i(0,0)+v_i/2) / v_i;
	mu = (t&((1<<bitLength)-1));

	return mu;			
}

int main()
{
	clock_t start,end;
	srand(1);

	start = clock();
	genKeys();
	end = clock();
	printf("gen time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);

	start = clock();
	CipherText c0 = enc(1);	
	end = clock();
	printf("enc time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);

	start = clock();
	printf("dec 0 : %d\n", dec(c0));
	end = clock();
	printf("dec time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);

	start = clock();
	//CipherText c1 = encSec(1);	
	CipherText c1 = enc(1);	
	end = clock();
	printf("enc time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);

	start = clock();
//	CipherText c3 = enc(3);	
	end = clock();
	printf("enc time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);
	
	start = clock();
	ZqMatrix  rplus = c0+c1; 
	end = clock();
	printf("+ time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);

	start = clock();
//	printf("dec + : %d\n", dec(rplus));
	end = clock();
	printf("dec time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);

	start = clock();
	ZqMatrix  rmul = c1*c0; 
	end = clock();
	printf("* time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);


	start = clock();
	printf("dec * : %d\n", dec(rmul));
	end = clock();
	printf("dec time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);

	start = clock();
	//printf("mp dec : %d\n", MPDec(c3,2));
	end = clock();
	printf("dec time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);



//	ZqMatrix  r2=c1+c1+c1, r3=c0+c1 , r4 = c0*c0, r5=c1*c1, r6=c0+c0;

	//printf("dec : %d %d %d %d %d %d\n", dec(r1), dec(r2), dec(r3), dec(r4), dec(r5), dec(r6));
//	printf("MPdec : %d\n", MPDec(r2,2));

/*
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++)
			printf("%d ", c1(i,j));
		printf("\n");
	}	
	printf("\n");
*/
	ZqMatrix f = rmul.flatten();
//	for(int i=0; i<N; i++) {
		for(int j=0; j<l; j++)
			printf("%d ", rmul(0,j));

	printf("\n");
		for(int j=0; j<l; j++)
			printf("%d ", f(0,j));
	
		printf("\n");
//	}	

	return 0;
}
