#include <stdlib.h>

int main()
{
  int nRows, nColumns;
  
  double **arr = (double**) malloc(nRows * sizeof(double*));
  for(int i = 0; i < nRows; i++) {
      arr[i] = (double*) malloc(nColumns * sizeof(double));
  }
  
  for(int i = 0; i < nRows; i++) {
      double* currentPtr = arr[i];
      free(currentPtr);
  } free(arr);
  
  return 0;
}
