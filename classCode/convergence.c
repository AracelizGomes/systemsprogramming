#include <stdio.h>
//An example to show when to use while do loop
//and when to use while loop
//September 9th, 2019
//Convergence

int main() {

	double x = 1.0, y;

	do {
		y = 0.5 * y;
		x = y;
	}while (y - x > 0.001 || y - x < -0.001);
	printf("%lf\n", y);


	int n;
	printf("Input an integer:\n");
	scanf("%d", &n);
	while(n > 1) {
		if (n % 2 == 0)
			n = n/2;
		else
			n = 3*n + 1;
		printf("%d\n", n);
	}
	return 0;

}

