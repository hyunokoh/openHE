#include "Poly.h"

int main()
{
        Poly a, b, c;
	a.randomize();
	b.randomize();

        c = a+b;
	a.print();
	b.print();
        c.print();

        c = a*b;
        c.print();

        return 0;
}

