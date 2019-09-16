#include <stdio.h>
#include <ctype.h>

#define     MIN_YEAR    1600
#define     MAX_YEAR    2399
#define     YEAR_OFFSET 2000

#define     RV_NODATE   0
#define     RV_VALIDDATE 1
#define     RV_INVALIDDATE 2

/***** DFA *****/

/* The function checks if a date is present at the beginning of a line,
 * and if the date is valid.
 *
 * Return values:
 *
 * 0:  Not date was found.
 * 1:  Date is valid.
 * 2:  Date was found, but not valid.
 */
int get_date() 
{
    getchar();
    return 0;
}

/***** main *****/
/* Do not change the main function. */
int main(void) 
{
    // run the loop until hit end of file
    do  {
        int rv = get_date();

        if (!feof(stdin)) {
            switch (rv) {
                case RV_NODATE:
                    printf("No date found.\n");
                    break;
                case RV_VALIDDATE:
                    printf("Valid date.\n");
                    break;
                case RV_INVALIDDATE:
                    printf("Invalid date.\n");
                    break;
                default:
                    printf("Unknown return value %d.\n", rv); 
                    break;
            }
        }
    } while (! feof(stdin));

    return 0;
}
