#include <stdio.h>


//this function tests if f1 is odd and if it is it returns 1 - if not it returns 0
int is_odd(int f1)
{
	if(f1%2 == 1)
	{
		return 1;
	}
	return 0;
}



//this function tests if f2 is prime: it returns 1 if its prime and 0 if its composite
int is_prime(int f2)
{
	int i;

	if (f2 < 2)
	{
		return 0;
	}

	if ((f2 % 2 == 0) && (f2 > 2))
	{
		return 0;
	}
	
	if (f2 == 2)
	{
		return 1;
	}

	for (i = 2; i < (f2 / 2); i++)
	{
		if ((f2 % i) == 0)
		{
			return 0;
		}
	}
	return 1;
}

		



//the fibonacci function calls the is_odd and is_prime functions and sums up all of the prime fibonacci
//numbers and sums up all of the odd fibonacci numbers smaller than the given limit parameter
int fib(int lim)
{
	//printf("%d \n", lim);
	int i, fi, f1, f2, sum_odd, num_prime;
	f1=0;
	f2=0;
	num_prime = 0;

	for(i=1; fi <= lim; i++)
	{
		//printf("%d \n", i);
				
		if (i >= 3)
		{
			fi = f1 + f2;
		}
		
		else
		{	
			fi=1;
		}

		if (is_odd(f1) == 1)
		{
		//	printf("%d\n",f1);
			sum_odd = sum_odd + f1;
		}
			
		if (fi < lim)		
		{	
			if(is_prime(i)==1)
			{
				//printf("f1 = %d f2 = %d fi = %d  lim = %d i = %d  \n",f1, f2, fi, lim, i);
				num_prime = num_prime + fi;
			}
		}
				
		f1 = f2;
		f2 = fi;
	
	}
	printf("\n odd total=");
	printf("%d", sum_odd);
	printf("\n prime indexed total=");
	printf("%d", num_prime);
	printf(" \n");

}

// the main function allows the code the code to be executed witha command line argument
int main(int argc, char *argv[])
{
	int lim, fi, f1, f2;
	lim = strtol(argv[1], NULL,10);
	//printf("%d \n", lim);
	fib(lim);
	
} 

