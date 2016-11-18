#include "Poly.h"

int main()
{
        Poly a, b, c;
        a.a[0] = 1;
        a.a[1] = 2;
        a.a[2] = 3;
        a.a[3] = 4;
        a.a[4] = 4;
        a.a[5] = 3;
        a.a[6] = 2;
        a.a[7] = 1;

	a.print();
	a.ntt(b);
	b.print();

//        c = a+b;
//        c.print();

//        c = a*b;
//        c.print();

        return 0;
}

