#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define BUFSIZE 80

// Reverse str, which has len characters.
// str may not have an ending NULL, but you already have len.
// suppose you have 10 chars to reverse:
// you swap 0 and 9, 1 and 8, 2 and 7 and so on.
void str_reverse(char str[], int len) 
{
    // TODO

	int i=0, k=len-1; // iterate over values and to swap letters
	char var;
	while (i < k)
	{
		var = str[i];
		str[i] = str[k];
		str[k] = var;
		k--;
		i++;			
	}
		
	printf("%s ", str);		
}	

int main() // 
{
	char ch = 0;
	char buf[BUFSIZE];
	int i = 0;
	int inWord = FALSE;

	while ((ch = getchar()) != EOF) 	{
        // isspace() may return non-zero values that is not 1. 
        // So be careful.
		int sp = isspace(ch);

        // depending on the value of ch and inWord.
        // You have four cases to handle.
        // TODO
        	if (i < BUFSIZE) {
			if (sp) { // if ch is a space
				if (inWord == FALSE){ //print a space
					if (i == 0)
					{
						printf(" ");
					}
				}

				else { // call the reverse function
					buf[i] = '\0';
					inWord = FALSE;
					str_reverse(buf, i);
					i=0;
				}
			}
        		else {
				buf[i]=ch; 
				inWord=1;
				i++; //increament
			}	
       	 	}
		else{
			exit(0);
		}

	}

    // What if the file does not end with a space?
    // TODO
	if (i>0){
		str_reverse(buf, i);
	}
	printf("\n");
	return 0;
}		






