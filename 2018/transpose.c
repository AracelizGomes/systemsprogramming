#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct Matrix {
    size_t row;
    size_t col;
    double **data;
};

typedef struct Matrix TMatrix;

/*
 * Creates and returns a matrix of size rows x cols
 * - rows : (non-negative value) giving the number of rows
 * - cols : (non-negative value) giving the number of columns
 * If the allocation is not successful, the function should return NULL
 * If the allocation is successful, the data field of the ADT should
 * point to an array of pointers (representing the rows) and each pointer
 * in that array should point to an array of double representing the values
 * in that row. 
 */
TMatrix * newMatrix(size_t rows, size_t cols) 
{
    // TODO 
	
	TMatrix * newmatrix;
	newmatrix = (TMatrix *)malloc(sizeof(TMatrix));

	if (cols < 0 || rows < 0) // negative value
    {
		return NULL;	
	}	
	else{ // non-negative value

	    newmatrix->row = rows; 
	    newmatrix->col = cols;
	    newmatrix->data = (double **)malloc(sizeof(double *) * rows); //point to an array of a double representing values in that row
	    int j;
	    for (j = 0; j < rows; j++){
            newmatrix->data[j] = (double *)malloc(sizeof(double *) * cols);
        }
        if (newmatrix->data == NULL)
            return NULL;
	}
	return newmatrix;
}

/*
 * This function is responsible for deallocating the dynamic memory
 * currently used by this matrix. Namely, it should deallocate the rows
 * and the array of row storage. 
 */
void freeMatrix(TMatrix * m) 
{
    /*
        Free the space for a matrix; the number of rows
        may be needed if each row is allocated with a
        separate malloc/calloc
    */
    // TODO
	int rows, cols;
	//TMatrix * cols;
	//m->row == rows;
	//m->col == cols;
	if (m == NULL)     /* remember to check m == NULL in every function */	
		return;
	
	else {
	    size_t rows = m->row;
		for (size_t i = 0; i < rows; i++){
			free(m->data[i]);	
		}
	}
	free(m->data);
	free(m);
	m = NULL;
}

/*
 * This function takes as input a matrix ADT and reads, from the standard
 * input, a collection of row x col doubles representing the content of the
 * matrix. Note that the content of the matrix should be given in row-major
 * order. Namely, the matrix
 * 1 2 3 
 * 4 5 6 
 * 7 8 9
 * should be conveyed with a white-space separated sequence of 9 numbers:
 * 1 2 3 4 5 6 7 8 9
 * If the input is malformed, the reading should be interrupted and the
 * function shall return the value 0 to report a failed read. 
 * If the input is well-formed, the reading should complete and the function
 * shall return the value 1. 
 */

int readMatrix(TMatrix * m) 
{
    
       // Read in from standard input the elements of a
       // rows X cols matrix, given row by row, and within
       // a row in increasing column order
    
	if (m == NULL)
		return 0;
    // TODO
    
	int i = 0, j = 0, counter = 1, data_read=0, rows=0, cols=0;
	rows = m->row;
	cols = m->col;
    size_t total = (rows * cols);
    while (counter <= total){ // counter goes up until it matrix ends
	    scanf("%d", &data_read);
	    m->data[i][j] = data_read;
	    j++;
        if (j == cols){ // if the j becomes =to the number of columns it reached the end of the                          row and has to go to the next row 
            j=0;
            i++;
        }
        counter++;
    }
	return 1;


}
/*
 * The transposeMatrix function takes as input a matrix ADT m and returns a
 * new TMatrix ADT that holds the transpose of m. Transposition should run in 
 * O(n x m)  (where n is the # of rows and m the # of columns). 
 * If memory allocation for the transpose failed, the routine should return
 * a 0x0 matrix ADT. 
 * Transposition follows the usual mathematical definition of transposition. 
 */

TMatrix * transposeMatrix(TMatrix * m) 
{
    
       
      // Allocate and return the address of a matrix that contains
       //the element of "a" in transposed order (with rows and columns
       //swapped)
    
    // TODO
    
    if (m == NULL)
        return NULL;
    TMatrix *transp = newMatrix(m->col, m->row);
    
    int i = 0, j = 0, rows= 0, cols = 0;
    rows = m->row;
    cols = m->col;
    
    for (i = 0; i < rows; i++){
        for (j = 0; j < cols; j++){
            transp->data[j][i] = m->data[i][j];
        }
    }
    
    return transp;


}

/*
 * The printMatrix function takes a matrix ADT as input and produces, on the
 * standard output, a representation of the matrix in row-major format. For
 * instance, the 3x3 identity matrix should print on 3 lines as:
 * 1 0 0 
 * 0 1 0
 * 0 0 1
 */
void printMatrix(TMatrix * m) 
{
    /*
       Print elements of rows X cols matrix a to standard output,
       one line per row
    */
    if (m == NULL)
        return;
    for (int i = 0; i < m->row; i++) {
        for (int j = 0; j < m->col; j++) 
            printf("%g ", m->data[i][j]);
        printf("\n");
    }
}

int main() 
{
    int     m = 0, n = 0;

    printf("Enter m and n (<= 0 to exit):\n");
    scanf("%d %d", &m, &n);

    while ((m > 0) && (n > 0)) {
        TMatrix * a = newMatrix(m, n);
        if (a != NULL) {
            printf("Enter %dx%d matrix:\n", m, n);
            if (readMatrix(a)) {
                printf("Input matrix:\n");
                printMatrix(a);

                TMatrix *t = transposeMatrix(a);
                if (t != NULL) {
                    printf("Transposed matrix:\n");
                    printMatrix(t);
                    freeMatrix(t);
                    printf("\n");
                } 
            } else {
                printf("Error while reading the matrix.\n");
            }
            freeMatrix(a);
        }
        printf("Enter m and n (<= 0 to exit):\n");
        int res = scanf("%d %d", &m, &n);
        if (res != 2) 
            m = 0;
    }
    return 0;
}
