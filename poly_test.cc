#include "Poly.h"

int main()
{
        Poly a, b, c;
        a.a[0] = 1;
        a.a[1] = 2;
        a.a[2] = 3;
        a.a[3] = 4;
        b.a[0] = 1;
        b.a[1] = 2;
        b.a[2] = 3;
        b.a[3] = 4;

        c = a+b;
        c.print();

        c = a*b;
        c.print();

        return 0;
}

