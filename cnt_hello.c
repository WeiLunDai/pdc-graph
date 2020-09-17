#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

int main() {
    FILE *op;
    op = fopen("output.txt", "w");
    while (true) {
        fprintf(op, "hello, world!\n");
        sleep(1);
    }
    return EXIT_SUCCESS;
}
