#include <stdio.h>
#include <stdlib.h>

void readPerm(int perm[], int len);
int  checkPerm(const int perm[], int len);

int main() 
{
    int length;
    int readOK;

    readOK = scanf("%d", &length);
    while (readOK && (length > 0)) {
        int perm[length+1];
        readPerm(perm, length);    

        int isSuper = checkPerm(perm, length); 
        printf("%ssuper\n", (isSuper ? "" : "not ")); 

        readOK = scanf("%d", &length);
    }
    return 0;
}

/*
    Read len integers, and save them to perm[1], perm[2], and so on.

    perm has (len + 1) elements. 0, 1, ..., len.
    perm[0] is not used. It is safe to write to perm[len].
*/
void readPerm(int perm[], int len)
{
    // Write a loop to read len integers.
    // In each iteration, use scanf to read an integer into 
    // a temporary variable, and then copy it to the right 
    // element in the array. 
    // Remember to start with perm[1].
    // TODO
	int p = 0;
	int val = 0;
	for (int i = 1; i <= len; i++){
	//	int p = 0;
	//	int val = 0;
		val = scanf("%d", &p);
		perm[i] = p;	
	}

}


// return 1 for superpermutations, 0 otherwise.
// remember 
//  1. perm has (len + 1) elements. perm[0] is not used. 
//  2. check if the value is between 1 and len.
int  checkPerm(const int perm[], int len)
{
    // TODO
	int isSuper = 1;
	int val = 0;
	for (int j = 1; j <= len; j++){ //iterate over with j
		val = perm[j];
		if ((j != perm[j]) || (j != perm[val])){ // if these cases are right then its not super
			isSuper = 0;
		}
	return isSuper;
	}
	
}




















