#ifndef _RGSW_PARAMETER_
#define _RGSW_PARAMETER_

#define N 1024 
#define Q 0x7FFE001
//#define N 8 
//#define Q 17 
//#define N 4 
//#define Q 5 
//#define L 31 	// L=31 is not working because Q is not 31 bit
#define L 27 
#define g 2
#define gInv 3
#define NInv 4

#define MOD(x) ((x)%Q)

#endif
