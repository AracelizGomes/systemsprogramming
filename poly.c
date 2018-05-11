#include <stdio.h>
#include <stdlib.h>

/*
 * Polynomial ADT. This data type uses two structures
 * Monomial: is used to represent a term  c * x^p
 *           where c is the coefficient and p is the power.
 * Polynomial: is used to capture an entire polynomial as a list
 *             of monomial. 
 * Note that the representation is sparse. Monomials with a coefficient
 * of zero should not be in the list. For instance, the polynomial:
 * 3 + 2 x + 4 x^3 - 7 x^10 would be represented by:
 * (10 , [(3,0), (2,1),(4,3),(-7,10)])
 * Where the first 10 is the degree of the polynomial and the list 
 * represent the 4 monomials with non-zero coefficients. 
 */
typedef struct Monomial {
    int coeff;     /* coefficient */
    int exp;       /* exponent    */
    struct Monomial *next;  /* next monomial */
} Mono;

typedef struct Polynomial {
    int   deg;     /* degree */
    Mono * first;   /* first monomial */
    Mono * last;    /* last monomial  */
} Poly;

/*
 * This function creates a new monomial with a given coefficient and power.
 * c : the coefficient
 * k : the power
 * The function allocates a monomial and initializes its attributes.
 * The return value is a pointer to the newly created monomial.
 */
Mono * newMono(int c, int k) 
{
    // TODO
    	Mono * newMonom;
	newMonom = (Mono*)malloc(sizeof(Mono));
	newMonom->coeff = c;
	newMonom->exp = k;
	newMonom->next = NULL;
	return newMonom;
}

/*
 * This function creates a new (empty) polynomial with degree 0 and no
 * monomials. 
 */
Poly * newPoly() 
{
    // TODO
	Poly * newPoly;
	newPoly = (Poly*)malloc(sizeof(Poly));
	newPoly->deg = 0;
	newPoly->first = NULL;
	newPoly->last = NULL;
	return newPoly;
}

/*
 * This function deallocates a polynomial.
 * p : the polynomial to deallocate
 * The function deallocates not-only the polynomials but also all the
 * monomials that it refers to (since those should not be shared anyway!)
 */
void freePoly(Poly * p) 
{
    // TODO
	if (p == NULL)
	{
		return;
	}
	Mono * mo1; //mono 1
	Mono * mo2 = p->first; // mono 2- first part of poly  is the mono2
	while (mo2 != NULL)
	{ // this condition will allow us to deallocate the monomials
		mo1 = mo2->next; 
		free(mo2);
		mo2 = mo1;
	}
	free(p);
}
	
/*
 * This functions adds a monomial inside a polynomial
 * p : the polynomial to modify
 * m : the monomial to add
 * The polynomial p is expected to be the sole owner of m. 
 * The new monomial should be added at the end of the list.
 * The degree of the monomial should not exceed the degree of the polynomial
 */
void appendMono(Poly * p, Mono * m) 
{
    // TODO

	if (p->last == NULL)
	{
		if  (p->deg == 0)
		{	
			p->first = m;
			p->last = m;
			p->deg = m->exp;
		}
		
		else if (p->deg > 0)
		{
			p->first = m;
			p->last = m;
		}
	}
	else {
		if((m->exp) <= (p->deg))
		{
			Mono * temp = p->last;
			temp->next = m;
			p->last = m; 
		}
	}	

}


/*
 * This function allocates, reads and returns a polynomial.
 * It starts by asking the highest degree
 * Then it reads all the monomials (which are given in increasing 
 * order of powers) as pairs of integers (whitespace separated) 
 * and adds them to the polynomial.
 * It finally returns the constructed poly.
 */
Poly * readPoly() 
{
    /*
       Add code to read from standard input a polynomial
       in the format described in the assignment document
       and construct its linked list representation
    */
    // TODO
 	int high_deg = 0, expo = 0, coef = 0;
	scanf("%d", &high_deg);
	Poly * newPolyn;
	Mono * newMonom;
	newPolyn = newPoly();
	newPolyn->deg = high_deg;
	
	while (expo <= high_deg){
		scanf("%d", &coef);
		scanf("%d", &expo);
		if (expo < high_deg)
		{
			newMonom = newMono(coef, expo);
			appendMono(newPolyn, newMonom);
		}

		else if (expo == high_deg){
			newMonom = newMono(coef, expo);
			appendMono(newPolyn, newMonom);
			break;
		}		
	}	
	return newPolyn;
}


/*
 * This function prints the received polynomial on the standard output.
 * p  : the polynomial to print.
 * Ouput: print the degree, then print a sequence of pairs coef power
 * end with a line feed. 
 */
void printPoly(Poly * p) 
{
     /*
     Add code to print to standard output a polynomial
     in the format described in the assignment document
    */
    if( p == NULL || p->first == NULL ) { // if either are finished/ have ended
        printf("empty\n");
        return;
    } else { /* print degree */
        printf( "%d ", p->deg );
        Mono * m = p->first;
        while( m != NULL ) {
            printf( "%d %d ", m->coeff, m->exp );
            m = m->next;
        }
        /* end with newline character */
        printf( "\n" );
   }
}

/*
 * The addPoly function computes a new polynomial that represent the sum of
 * its inputs. 
 * p1  : first polynomial
 * p2  : second polynomial
 * Assumptions: 
 * - both p1 and p2 list monomials in increasing powers.
 * - p1 and p2 do NOT have to have the same degree
 * - p1 and p2 are NOT expected to have the same number of monomials
 * - p1 and p2 are NOT expected to have monomials of matching degrees (they might)
 * - The treatment is NOT destructive. p1 and p2 are untouched.
 * Output:
 * A new polynomial is allocated, filled and returned. 
 * Notes:  
 * - monomials of the same power from p1 and p2, should be aggregated.
 * - monomials with a zero coefficient should be discarded.
 * - the degree of the answer should be the highest power with a non-zero coef. 
 */
Poly * addPoly(Poly * p1,Poly * p2) 
{
   
   //  Add code to compute the sum of two polynomials
   //  given as linked lists     
    // TODO

   	Poly * newPol; // new poly	
	newPol = newPoly();
	Mono * newMon;
	Mono * buffer1 = p1->first; // first place holder
	Mono * buffer2 = p2->first;// second
	int highest=0;
	if (p1->deg >= p2->deg) {
		highest = p1->deg;
	}
	else{
		highest = p2->deg;
	}
	newPol->deg = highest;
	int total, pow = 0;

	while (buffer1 != NULL && buffer2 != NULL)// loop until end of linked list 1 & 2 
	{
		total = 0; 
		if (buffer1->exp > buffer2->exp)
		{ //exp1 is greater so work on 2
			pow = buffer2->exp;
			total = buffer2->coeff;
			newMon = newMono(total, pow);
		//	newMon = newMono((buffer2->coeff), (buffer2->exp));
			appendMono(newPol, newMon);
			buffer2 = buffer2->next;
		}
		else if (buffer1->exp < buffer2->exp)
		{ //exp2 is greater so work on 1
			pow = buffer1->exp;
			total = buffer1->coeff;
			newMon = newMono(total, pow);
		//	newMon = newMono((buffer1->coeff), (buffer1->exp));
			appendMono(newPol, newMon);
			buffer1 = buffer1->next;		
		}
		else if (buffer1->exp == buffer2->exp)	{
		//exponents are equal so work on both!
			pow = buffer1->exp;
			total = (buffer1->coeff) + (buffer2->coeff);
			newMon = newMono(total, pow);
		//	newMon = newMono(((buffer1->coeff)+(buffer2->coeff)), (buffer1->exp));
			appendMono(newPol, newMon);
			buffer1 = buffer1->next;
			buffer2 = buffer2->next;		
		}
		else if (buffer1 == NULL){
		// if polynominal 1 has ended and the second hasnt
			pow = buffer2->exp;
			total = buffer2->coeff;
			newMon = newMono(total, pow);
		//	newMon = newMono((buffer2->coeff), (buffer2->exp));
			appendMono(newPol, newMon);
			buffer2 = buffer2->next;

		}
		else if (buffer2 == NULL)
		{//if poly 2 has ended but not 1
			pow = buffer1->exp;
			total = buffer1->coeff;
			newMon = newMono(total, pow);
	//		newMon = newMono((buffer1->coeff), (buffer1->exp));
			appendMono(newPol, newMon);
			buffer1 = buffer1->next;
		}
	}
	return newPol;
}

/***************************************************/

int main() 
{
    Poly * p1 = readPoly();
    Poly * p2 = readPoly();
    Poly * sum;

    if( (p1 == NULL) || (p2 == NULL) )
    {
        fprintf(stderr, "Could not allocate memory\n");
        return 1;
    }
    printPoly(p1);
    printPoly(p2);
    printf("\n");
    
    printPoly( sum = addPoly( p1, p2 ) );

    freePoly(p1);
    freePoly(p2);
    freePoly(sum);
    return 0;
}

/***************************************************/
