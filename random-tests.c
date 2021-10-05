#include <stdio.h>
#include <stdlib.h>

// ----------------------------------------------------------------------------

void example1()
{
    double arr[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 4; j++) {
            printf("%4.f ", arr[i][j]);
        } printf("\n");
    }
}

// ----------------------------------------------------------------------------

void example2()
{
    double sArr[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    double** dArr = (double**) malloc(3 * sizeof(double *));
    for(int i = 0; i < 3; i++) {
        dArr[i] = (double*) malloc(4 * sizeof(double));
    }

    printf("-------------------------------\n");
    printf(" sArr       : %p\n", sArr);
    printf(" sArr[0]    : %p\n", sArr[0]);
    printf(" sArr[0][0] : %p\n", sArr[0][0]);
    printf("&sArr[0][0] : %p\n", &(sArr[0][0]));
    printf("-------------------------------\n");
    printf("&sArr[0][0] : %p\n", &(sArr[0][0]));
    printf("&sArr[0][1] : %p\n", &(sArr[0][1]));
    printf("&sArr[0][2] : %p\n", &(sArr[0][2]));
    printf("&sArr[0][3] : %p\n", &(sArr[0][3]));
    printf("&sArr[1][0] : %p\n", &(sArr[1][0]));
    printf("&sArr[1][1] : %p\n", &(sArr[1][1]));
    printf("&sArr[1][2] : %p\n", &(sArr[1][2]));
    printf("&sArr[1][3] : %p\n", &(sArr[1][3]));
    printf("&sArr[2][0] : %p\n", &(sArr[2][0]));
    printf("&sArr[2][1] : %p\n", &(sArr[2][1]));
    printf("&sArr[2][2] : %p\n", &(sArr[2][2]));
    printf("&sArr[2][3] : %p\n", &(sArr[2][3]));
    printf("-------------------------------\n");
    printf("&dArr[0][0] : %p\n", &(dArr[0][0]));
    printf("&dArr[0][1] : %p\n", &(dArr[0][1]));
    printf("&dArr[0][2] : %p\n", &(dArr[0][2]));
    printf("&dArr[0][3] : %p\n", &(dArr[0][3]));
    printf("&dArr[1][0] : %p\n", &(dArr[1][0]));
    printf("&dArr[1][1] : %p\n", &(dArr[1][1]));
    printf("&dArr[1][2] : %p\n", &(dArr[1][2]));
    printf("&dArr[1][3] : %p\n", &(dArr[1][3]));
    printf("&dArr[2][0] : %p\n", &(dArr[2][0]));
    printf("&dArr[2][1] : %p\n", &(dArr[2][1]));
    printf("&dArr[2][2] : %p\n", &(dArr[2][2]));
    printf("&dArr[2][3] : %p\n", &(dArr[2][3]));
    printf("-------------------------------\n");
}

// ----------------------------------------------------------------------------

void example3()
{
    //
}

// ----------------------------------------------------------------------------

void example4()
{
    int num1;
    double num2;
    void* arr[3];

    int* p1 = &num1;
    double* p2 = &num2;
    char* p3 = "Hello World";

    arr[0] = p1;
    arr[1] = p2;
    arr[2] = p3;

    *p1 = 3.7;
    *p2 = 7.4;

    printf("%d\t%f\t%s", *((int*) arr[0]), *((double*) arr[1]), arr[2]);
}

// ----------------------------------------------------------------------------

void example5()
{
    int dummy[3] = {3, 6, 9};

    for(int i = 0; i < 3; i++)
        printf("%i\t", dummy[i]);
    printf("\n");

    for(int i = 0; i < 3; i++)
        printf("%p\t", &dummy[i]);
    printf("\n");

    for(int i = 0; i < 3; i++)
        printf("%p\t", &dummy[i] + 1);
    printf("\n");

    for(int i = 0; i < 3; i++)
        printf("%p\t", ((size_t) &dummy[i]) + 2);
    printf("\n");

    int* segFault = (int*) (((size_t) &dummy[0]) + 2);
    printf("%p", segFault);
    printf("\n");
    printf("%d", segFault);

    printf("\n");
    printf("Should not reach here");
}

// ----------------------------------------------------------------------------

int main()
{
    // example1();
    // example2();
    // example3();
    // example4();
    // example5();
}

// ----------------------------------------------------------------------------
