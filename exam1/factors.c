#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* factors */
typedef struct factor_tag {
    long    prime;              // prime factor
    long    e;                  // exponent
    struct factor_tag *next;    // to next prime factor
} factor_t;

/* integer type. 
 * factors points to the first prime factor, and 
 * it is NULL if the integer is 1.
 * */
typedef struct integer_tag {
    factor_t *factors;
} integer_t;

int isprime(int n)
{
	int i, output;
	scanf("%d", &n);
		if (n < 2)
	{
		output=0;	
	}
	
	if (n == 2)
	{
		output=1;
	}

	else
	{
		for (i=2; (i*i)<=n; i++)
		{
			if ((n% i)==0)
			{
				output=0;
			}	
			else
			{
				output=1;
			}
		}
		
	
	}
	
	return output;

}

/* given a postive integer n > 1, this function returns its  
 * smallest prime factor. 
 * Note that any integer greater than 1 has a prime factor.
 * You may copy and revise the code from isprime() function.
 */
long get_prime_factor(long n)
{
	if (n <= 1)
		return 0;

    // TODO
 	int i;
	else{
		for (i=0; i<=n; i++){
			if (isprime(i))
				return i;
				break;
		}
		
	}
	
    return 0;
}

/* Add prime number and exponent to the list. 
 * assume the primes are added to the list in ascending order.
 * However, a prime may be added multiple times.
 *
 * Create a new node inside this function.
 * You can exit from the program if malloc fails.
 *
 * Return the new head of the list.
 * */
static factor_t * add_prime_factor (factor_t * first, long prime, long e)
{
    // TODO
    return NULL;
}

/* 
 * The function returns a pointer to integer_t.
 * If n is greater than 1, create a list of prime factors for n. 
 * Note that the primes on the list are in ascending order.
 * If n is 1, the list is empty.
 * If n is less than 1, return NULL.
 *
 * You can exit from the program if malloc fails. 
 * */
integer_t * new_integer(long n)
{
    // TODO
    if (n < 1)
        return NULL;
    return NULL;
}

/* free all memory space used by an intger */
void delete_integer(integer_t * a)
{
    // TODO
}

/* Multiply two integers a and b. 
 * Return a pointer to the product.
 *
 * Return NULL if a or b is NULL.
 *
 * You can exit from the program if malloc fails. 
 */
integer_t * mul_integers(integer_t *a, integer_t *b)
{
    // TODO
    if (a == NULL || b == NULL)
        return NULL;

    return NULL;
}

/* Find gcd of two integers a and b. 
 * Return a pointer to gcd.
 * Note that gcd can be 1 if a and b are coprime or one of them is 1.
 *
 * Return NULL if a or b is NULL.
 *
 * You can exit from the program if malloc fails. 
 */
integer_t * gcd_integers(integer_t *a, integer_t *b)
{
    // TODO
    if (a == NULL || b == NULL)
        return NULL;

    return NULL;
}

/*==============================================*/
/* Do not change any code below */
/*==============================================*/

/* print an integer */
void print_integer(integer_t *a)
{
    if (a == NULL) {
        printf("InvalidInt");
        return;
    }

    if (a->factors == NULL) {
        printf("1");
        return;
    }

    factor_t *p = a->factors;

    /* print factors. It is a valid Python expression.*/
    while (p) {
        printf("%s%ld**%ld", ((p == a->factors) ? "" : " * "), p->prime, p->e);
        p = p->next;
    }
}

/* do not change main() function */
int main(int argc, char **argv)
{
    long a, b;

    if (argc == 3) { 
        a = atol(argv[1]);
        b = atol(argv[2]);
    }
    else {
	printf("Usage: %s PositiveInteger1 PositiveInteger2\n", argv[0]); 
	return -1;
    }

    if (a < 1 || b < 1) {
        printf("Both integers must be positive.");
        return -2;
    }

    integer_t  *aInt = new_integer(a);
    integer_t  *bInt = new_integer(b);
    integer_t  *cInt = mul_integers(aInt, bInt);
    integer_t  *dInt = gcd_integers(aInt, bInt);

    printf("%ld=", a);
    print_integer(aInt);
    printf("\n%ld=", b);
    print_integer(bInt);
    printf("\n%ld*%ld=%ld=", a, b, a*b);
    print_integer(cInt);
    printf("\ngcd(%ld,%ld)=", a, b);
    print_integer(dInt);
    printf("\n");

    delete_integer(aInt); 
    delete_integer(bInt); 
    delete_integer(cInt); 
    delete_integer(dInt); 

    return 0;
}
