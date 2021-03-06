#include <stdlib.h>

void fill2DArray(double** matrix, int nRows, int nColumns, double initialValue)
{
  for(int i = 0; i < nRows; i++) {
    for(int j = 0; j < nColumns; j++) {
      matrix[i][j] = initialValue;
    }
  }
}

int main()
{
  // 2D Array
  int nRows, nColumns;
  
  double** arr = (double**) malloc(nRows * sizeof(double*));
  for(int i = 0; i < nRows; i++) {
      arr[i] = (double*) malloc(nColumns * sizeof(double));
  }
  
  fill2DArray(arr, nRows, nColumns, 0.0);
  
  for(int i = 0; i < nRows; i++) {
      double* currentPtr = arr[i];
      free(currentPtr);
  } free(arr);
  // Not sure if we should free the arr itself
  // some people say it is necessary; other say
  // that it is actually unnecessary (or even wrong)
  // also, compiler warn when trying to free the arr
  // Just to remind myself to search about this later
  
  // End
  return 0;
}
