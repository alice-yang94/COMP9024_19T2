#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int error = 0;
    if (argc != 2) {
        fprintf(stderr, "Usage: ./count+ number\n");
        error = 1;
    } else {
        int num;
        if (sscanf(argv[1], "%d", &num) != 1) {
            fprintf(stderr, "Usage: ./count+ number\n");
            error = 1;
        } else {
            if (num < 0) {
                fprintf(stderr, 
                    "input should be a non-negative integer\n");
                error = 1;
            } else {
                for (int i=0; i<num; i++) {
                    printf("%d,",i);
                }
                printf("%d",num);
                putchar('\n');
            }
        }
    }
    if (error) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}