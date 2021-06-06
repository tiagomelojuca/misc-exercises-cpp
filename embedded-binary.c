#include <stdio.h>
#include "binary.h"

int main () {
    // raw_data obtained with: xxd -i binary.exe >> binary.h
    FILE *write_ptr = fopen("binary.exe", "wb");
    fwrite(raw_data, sizeof(raw_data), 1, write_ptr);
    fclose(write_ptr);

    return 0;
}
