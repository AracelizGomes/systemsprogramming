/* Compute e ** x, using Taylor series.  */

#include <stdio.h>
#include <stdlib.h>

double factorial(double n){
	if (n < 0)
		return 0;
	if (n == 0 || n==1)
		return 1;
	else
		return (n*factorial(n-1));
}

double power(double x, int i){
	if (i == 0)
		return 1.0;
	else
		return x*power(x, i-1);
}


double main(void){
	double x, sum;
	int i, n;
	while (scanf("%lf%d", &x, &n) == 2){
		sum = 0.0;
		for (i=0; i<n; i++){
			double numerator = power(x,i);
			double denominator = factorial(i);
			sum += (numerator / denominator);
		}
		
		printf("exp(%.10lf)=%.10lf\n", x, sum);
	}
	return 0;
}
