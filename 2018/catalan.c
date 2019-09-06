#include <stdio.h>
#include <stdlib.h>

/* This function calculates Catalan number n. 
 * If n is invalid, return 0.
 * Do not worry about overflow.
 * Do not print anything in this function.
 */
static long catalan_number(int n)
{
	double top, val;
	if (n < 0)
		return 0;
    // TODO
  	if (n==1 || n==0)
		return 1;
	else {
		//int c;
		top = ((4*n) - 2);
		val = top/(n+1)*catalan_number(n-1);		
	}
	return val;

}

/* do not change main function */
int main(int argc, char **argv)
{
    int n = 100;

    if (argc == 2) { 
        n = atoi(argv[1]);
    } else if (argc == 1) {
        scanf("%d", &n);
    } 
    
    if (n > 40) {
	printf("Please specify an integer less than 41.\n"); 
	return 1;
    }
    printf("C(%d)=%ld\n", n, catalan_number(n));
    return 0;
}
