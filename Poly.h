#ifndef _POLY_
#define _POLY_

#define N 4
#define Q 5
#define g 2
#define gInv 3
#define NInv 4

class Poly {
public:
        int a[N];

        Poly ntt(Poly& a, int wn, int n);
        Poly nttInv(Poly& a, int wn, int n);

        Poly operator+(Poly&);
        Poly operator*(Poly&);

        void print();
};


#endif
