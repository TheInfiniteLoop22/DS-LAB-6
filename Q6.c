// Given an array, print the Next Greater Element (NGE) for every element using stack. 
// The Next Greater Element for an element x is the first greater element on the right 
// side of x in array. Elements for which no greater element exist, consider next greater 
// element as -1. For the input array [13, 7, 6, 12}, the next greater elementsfor each 
// element are as follows.
// Element NGE
// 13 → -1
// 7 → 12
// 6 → 12
// 12 → -1

#include <stdio.h>
#include <stdlib.h>

int next_greater_element(int arr[], int n) {
    int *nge = (int *)malloc(n * sizeof(int));
    int stack[n];
    int top = -1;

    for (int i = n - 1; i >= 0; i--) {
        while (top != -1 && arr[stack[top]] <= arr[i]) {
            top--;
        }

        if (top != -1) {
            nge[i] = arr[stack[top]];
        } else {
            nge[i] = -1;
        }

        stack[++top] = i;
    }

    for (int i = 0; i < n; i++) {
        printf("%d -> %d\n", arr[i], nge[i]);
    }

    free(nge);
}

int main() {
    int arr[] = {13, 7, 6, 12};
    int n = sizeof(arr) / sizeof(arr[0]);
    next_greater_element(arr, n);
    return 0;
}
