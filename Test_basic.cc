#include "FHE.h"
#include <stdlib.h>
#include <stdio.h>

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
	CipherText c0 = gsw.enc(0);	
	end = clock();
	printf("enc time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);

	start = clock();
	printf("dec 0 : %d\n", gsw.dec(c0));
	end = clock();
	printf("dec time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);

	start = clock();
	//CipherText c1 = gsw.encSec(1);	
	CipherText c1 = gsw.enc(1);	
	end = clock();
	printf("enc time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);

	start = clock();
	CipherText c3 = gsw.enc(3);	
	end = clock();
	printf("enc time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);
	
	start = clock();
	ZqMatrix  rplus = c0+c1; 
	end = clock();
	printf("+ time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);

	start = clock();
	printf("dec + : %d\n", gsw.dec(rplus));
	end = clock();
	printf("dec time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);

	start = clock();
	ZqMatrix  rmul = c0*c1; 
	end = clock();
	printf("* time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);


	start = clock();
	printf("dec * : %d\n", gsw.dec(rmul));
	end = clock();
	printf("dec time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);

	start = clock();
	printf("mp dec : %d\n", gsw.MPDec(c3,2));
	end = clock();
	printf("dec time : %f\n", (float)(end-start)/CLOCKS_PER_SEC);

	CipherText notc0 = !c0;
	printf("not %d =  %d\n", gsw.dec(c0), gsw.dec(notc0));

	CipherText notc1 = !c1;
	printf("not %d =  %d\n", gsw.dec(c1), gsw.dec(notc1));

	return 0;
}
