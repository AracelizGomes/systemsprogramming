/*
Compute the sum of integers
from 1 to n, for the given n
*/

#include <stdio.h>

int main(void) {
	int i, n, sum;
	sum = 0;
	printf("Enter a value n:\n");
	scanf("%d", &n);
	for (i=0; i<=n; i++){
		sum = sum + i;
	}
	printf("The sum is %d\n", sum);
	return sum;

}
