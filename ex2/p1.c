#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(void){
int a;
//a = malloc(sizeof(int *) * 300);
int a[300][100];
char c[] = "1234567";

//int x = malloc(sizeof(int *) * 100);

int r = (sizeof(c)) == (strlen(c));

for (int i = 0; i < (sizeof(x)); i++){
    x[i] = strlen(a);
}


printf("%d", (sizeof(a)));
printf( &a[10][20]);

printf("%d", (r));

return 0;

}
