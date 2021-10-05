#include <stdio.h>

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
    // todo::write example 2
}

// ----------------------------------------------------------------------------

void example3()
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

void example4()
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
}

// ----------------------------------------------------------------------------
