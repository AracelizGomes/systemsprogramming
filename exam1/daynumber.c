#include <stdio.h>
#include <stdlib.h>

/* Arguments: 
 * d: day of the month (1 to 28,29,30, or 31, depending on month).
 * m: 1 - 12. (1 for Jan, 2 for Feb, and so on).
 * y: 1900 to 2999
 * returns day number if input is valid, and return 0 otherwise.
 * */
static int  day_number_in_year(int d, int m, int y)
{
	int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int days=0, total=0;
    // TODO 
    // return 0 if anything wrong
    
	if (y < 1900 || y > 2999)	
		return 0;
	
	if (y>=1900 || y<= 2999) {
	
	if ((d > daysInMonth[m-1]) && (y%400!=0))
		return 0;
 
	else {
		//	days = (((m-1)*(daysInMonth[m-1])) + d);
		//	printf("%d", days);
		//	printf("%d", m);
		
		for (int i=0; i < (m-1); i++){
			days += daysInMonth[i];
		//	return days;
		}	
		}
		
		total = days+d;
		
	if (y%400==0)
		total +=1;
	else
		total = total;				
			

	//return total; 			
	
}
return total;
}
/* do not change anything below */
int main(int argc, char **argv)
{
    int  m, d, y;

    if (argc == 4) { 
        m = atoi(argv[1]);
        d = atoi(argv[2]);
        y = atoi(argv[3]);
    }
    else {
	printf("Usage: %s <month> <day> <year>\n", argv[0]); 
	return 1;
    }

    printf("%d\n", day_number_in_year(d, m, y));

    return 0;
}
