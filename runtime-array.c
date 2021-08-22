#ifndef RUNTIME_ARRAY_H
#define RUNTIME_ARRAY_H

#define CREATE_MATRIX(T, arr, rows, cols, defVal)    \
    const int _internalLibRows##arr = rows;          \
    const int _internalLibCols##arr = cols;          \
    T** arr = (T**) malloc(rows * sizeof(T*));       \
    for(int i = 0; i < rows; ++i) {                  \
        arr[i] = (T*) malloc(cols * sizeof(T));      \
        for(int j = 0; j < cols; ++j) {              \
            arr[i][j] = defVal;                      \
        }                                            \
    }

#define FREE_MATRIX(arr)                             \
    for(int i = 0; i < _internalLibRows##arr; ++i) { \
        free(arr[i]);                                \
    } free(arr);

#endif // RUNTIME_ARRAY_H
