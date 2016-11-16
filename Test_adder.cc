#include "FHE.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


void add1bit(CipherText& theCout, CipherText& sum, CipherText& theCin, CipherText& a, CipherText& b)
{
	sum = a+b+theCin;

	theCout = a*b + b*theCin + a*theCin;
	//theCout = (a&b)&((a+b)&theCin)
		//theCout = id(N, 1)-((id(N, 1)-(a*b))*((id(N, 1)-((a+b)*theCin))));
}

void add2bit(CipherText& theCout, CipherText& sum1, CipherText& sum2,CipherText& theCin, CipherText& a, CipherText& b,CipherText& c, CipherText& d)
{
	sum1 = a+b+theCin;
	//sum2 = c+d+theCin;
	//CipherText& Temp = a*b+b*theCin+theCin*a;
	CipherText Temp;
	
	Temp = a*b+b*theCin+theCin*a;
	add1bit(theCout,sum2,Temp,c,d);
	//theCout = (a&b)&((a+b)&theCin)
		//theCout = id(N, 1)-((id(N, 1)-(a*b))*((id(N, 1)-((a+b)*theCin))));
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
	CipherText c = gsw.enc(1);
	CipherText d = gsw.enc(0);	
	end = clock();
	printf("enc time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);

	printf("dec  : cin = %d, a = %d, b = %d\n c = %d, d= %d\n", gsw.dec(one), gsw.dec(a), gsw.dec(b), gsw.dec(c), gsw.dec(d));

	start = clock();
	CipherText cout1, s1,s2;
	//add1bit(cout1, c, one, a, b);
	add2bit(cout1,s1,s2,one,a,b,c,d);
	end = clock();
	printf("2 bit adder time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);

	start = clock();
	printf("dec  : cout = %d, sum1 = %d\n, sum2 = %d\n", gsw.dec(cout1), gsw.dec(s1),gsw.dec(s2));
	end = clock();
	printf("dec time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);

	return 0;
}
