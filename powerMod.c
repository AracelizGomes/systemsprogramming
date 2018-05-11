#include <stdio.h>

static long powerMod(long n, long e, long m) {
	/* Implement the function here. It returns -1 on all input for now. */
	if (n <= 0 || e<=0 || m<=1)
	{
		return -1;
	}
	int result = 1;

	while (e > 0)
	{
		if (e%2 != 0)
		{
			result = (result*n) % m;
		}
		e = e/2;
		n = (n*n) % m;
	}
	return result;

}

int main() {
	printf("Please enter n, e, and m:"); 
	long n, e, m;
	scanf("%ld %ld %ld",&n, &e, &m);
	printf("%ld ^ %ld mod %ld = %ld\n", n, e, m, powerMod(n, e, m));
	return 0;
}
