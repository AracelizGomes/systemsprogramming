#include <stdio.h>

/* Search for `count' distinct odd numbers that 
 * are smaller than `bound' and add up to `sum'.  
 *
 * Return value:
 *  1: A solution is found and printed.
 *  0: No solution was found.
 */
int odd_sum(int count, int bound, int sum)
{
    return 0;
}

/* Do not change the main() function */
int main(void)
{
    int value;
    int c, b, s;

    printf("Please enter 3 positive integers: count, bound, and sum:\n");
    if (scanf("%d%d%d", &c, &b, &s) != 3) {
        printf("Please enter 3 integers.\n");
        return 1;
    }

    if (c <= 0 || b <= 0 || s <= 0) {
        printf("Integers must be positive.\n");
        return 1;
    }

    value = odd_sum(c, b, s);
    if (value)
        printf("\n");
    else
        printf("There are no solutions.\n");
    return 0;
}
