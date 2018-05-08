#include <stdio.h>
#include <stdlib.h>

int main() {

	int i = 1, j=2, k=3;
	int a[]= {5, 15, 20, 25};
	int *p = a;

	int y = (!i || j^j);
	printf("1 is %i\n", y);

	int aa = ((k++)%j);
	printf("2 is %i\n", aa);

	int b = (int)(i/j*10.0);
	printf("3 is %i\n", b);
	

	int cc = (2*i-(5<k));
	printf("4 is %i\n", cc);

	int d = (i=10, j=i+5, j-10);
	printf("5 is %i\n", d);

	int yy = (i + 5 < j ? i : j < k ? j:k);
	printf("6 is %i\n",yy );

	int zz= (j << i+1);
	printf("7 is %i\n", zz);

	int jj= (a[0]=*(p+2));
	printf("8 is %i\n", jj);

	int gg= (&a[3]-p);
	printf("9 is %i\n", gg);

	int ll= (*++p);
	printf("10 is %i\n", ll);
return 0;

}
