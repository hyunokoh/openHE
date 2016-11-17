#include "RGSW.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
	clock_t start,end;
	srand(1);

	RGSW gsw;

	start = clock();
	gsw.genKeys();
	end = clock();
	printf("gen time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);

	start = clock();
	RingCipherText c0 = gsw.enc(0);	
	end = clock();
	printf("enc time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);


	start = clock();
	printf("dec 0 : %d\n", gsw.dec(c0));
	end = clock();
	printf("dec time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);

	start = clock();
	RingCipherText c1 = gsw.enc(1);	
	end = clock();
	printf("enc time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);
	printf("dec 1 : %d\n", gsw.dec(c1));

	start = clock();
	RingCipherText  rplus = c0+c1; 
	end = clock();
	printf("+ time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);

	start = clock();
	printf("dec + : %d\n", gsw.dec(rplus));
	end = clock();
	printf("dec time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);

	start = clock();
	RingCipherText  rmul(c0.getNumRows(),c1.getNumCols());
	mulCipherText(rmul,c0,c1); 
	end = clock();
	printf("* time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);


	start = clock();
	printf("dec * : %d\n", gsw.dec(rmul));
	end = clock();
	printf("dec time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);

	return 0;
}
