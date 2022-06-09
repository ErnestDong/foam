#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    int *ptr = malloc(sizeof(int));
    *ptr = 1;
    free(ptr);
    *ptr = 2;
    printf("%d\n", *ptr);
    return 0;
}
