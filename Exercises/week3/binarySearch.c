#include <stdio.h>
#include <stdlib.h>
int binarySearch(int a[], int n, int key);

int main(int argc, char *argv[]) {
    int found = binarySearch((int[]){2,1,4,3,5,6}, 6, 100);
    printf("found: %d\n", found);

    return EXIT_SUCCESS;
 }

int binarySearch(int a[], int n, int key) {
    int found = 0;
    int low = 0;
    int high = n-1;
    int mid;
    while (!found && low <= high) {
        mid = (low+high)/2;
        if (a[mid] == key) {
            found = 1;
        } else if (a[mid] < key) {
            low = mid + 1;
        } else {
            high = mid + 1;
        }
    }
    return found;
}