#include "FHE.h"
#include <stdlib.h>
#include <stdio.h>

void add1bit(CipherText& theCout, CipherText& sum, CipherText& theCin, CipherText& a, CipherText& b)
{
	sum = a+b+theCin;

	theCout = a*b + b*theCin + theCin*a;
}

int main()
{
	clock_t start,end;
	srand(1);

	FHE gsw;

	start = clock();
	gsw.genKeys();
	end = clock();
	printf("gen time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);

	start = clock();
	CipherText one = gsw.enc(1);	
	CipherText a = gsw.enc(1);	
	CipherText b = gsw.enc(1);	
	end = clock();
	printf("enc time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);

	printf("dec  : cin = %d, a = %d, b = %d\n", gsw.dec(one), gsw.dec(a), gsw.dec(b));

	start = clock();
	CipherText cout1, c;
	add1bit(cout1, c, one, a, b);
	end = clock();
	printf("1 bit adder time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);

	start = clock();
	printf("dec  : cout = %d, sum = %d\n", gsw.dec(cout1), gsw.dec(c));
	end = clock();
	printf("dec time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);

	return 0;
}
