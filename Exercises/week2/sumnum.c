#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
    int sumArgs = 0;
    for (int i=1; i<argc; i++) {
        int currNum;
        if (sscanf(argv[i],"%d",&currNum) != 1) {
            fprintf(stderr,
                    "Error: argument %s is non-numeric!\n",
                    argv[i]);
            return EXIT_FAILURE;
        }

        sumArgs += currNum;
    }
    if (argc > 1) printf("%d\n",sumArgs);
    return EXIT_SUCCESS;
}