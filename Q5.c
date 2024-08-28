// Write a program to implement multiple stacks (say n stacks) in a single array.
// Implement ADD(i. X) and DELETE(i) to add X and delete an element from stack i,
// 1<= i <= n.

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define ARRAY_SIZE 100
#define MAX_STACKS 10

typedef struct {
    int *array;
    int *top;
    int *base;
    int n;
} MultiStack;

MultiStack* createMultiStack(int n) {
    if (n <= 0 || n > MAX_STACKS) {
        printf("Invalid number of stacks\n");
        return NULL;
    }

    MultiStack *ms = (MultiStack*)malloc(sizeof(MultiStack));
    if (!ms) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    ms->array = (int*)malloc(ARRAY_SIZE * sizeof(int));
    ms->top = (int*)malloc(n * sizeof(int));
    ms->base = (int*)malloc(n * sizeof(int));
    ms->n = n;

    if (!ms->array || !ms->top || !ms->base) {
        printf("Memory allocation failed\n");
        free(ms->array);
        free(ms->top);
        free(ms->base);
        free(ms);
        return NULL;
    }

    int stackSize = ARRAY_SIZE / n;
    for (int i = 0; i < n; i++) {
        ms->base[i] = i * stackSize;
        ms->top[i] = ms->base[i] - 1;
    }

    return ms;
}

int isFull(MultiStack *ms, int stackNum) {
    if (stackNum < 0 || stackNum >= ms->n) {
        return -1;  // Invalid stack number
    }
    return (stackNum == ms->n - 1) ? 
           (ms->top[stackNum] == ARRAY_SIZE - 1) : 
           (ms->top[stackNum] == ms->base[stackNum + 1] - 1);
}

int isEmpty(MultiStack *ms, int stackNum) {
    if (stackNum < 0 || stackNum >= ms->n) {
        return -1;  // Invalid stack number
    }
    return ms->top[stackNum] == ms->base[stackNum] - 1;
}

void add(MultiStack *ms, int stackNum, int value) {
    if (stackNum < 0 || stackNum >= ms->n) {
        printf("Invalid stack number\n");
        return;
    }

    if (isFull(ms, stackNum)) {
        printf("Stack %d is full\n", stackNum);
        return;
    }

    ms->top[stackNum]++;
    ms->array[ms->top[stackNum]] = value;
    printf("Added %d to stack %d\n", value, stackNum);
}

int delete(MultiStack *ms, int stackNum) {
    if (stackNum < 0 || stackNum >= ms->n) {
        printf("Invalid stack number\n");
        return INT_MIN;
    }

    if (isEmpty(ms, stackNum)) {
        printf("Stack %d is empty\n", stackNum);
        return INT_MIN;
    }

    int value = ms->array[ms->top[stackNum]];
    ms->top[stackNum]--;
    printf("Deleted %d from stack %d\n", value, stackNum);
    return value;
}

void freeMultiStack(MultiStack *ms) {
    if (ms) {
        free(ms->array);
        free(ms->top);
        free(ms->base);
        free(ms);
    }
}

int main() {
    int n;
    printf("Enter the number of stacks (1-%d): ", MAX_STACKS);
    scanf("%d", &n);

    MultiStack *ms = createMultiStack(n);
    if (!ms) {
        return 1;
    }

    int choice, stackNum, value;
    do {
        printf("\n1. Add element\n2. Delete element\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter stack number (0-%d) and value: ", n-1);
                scanf("%d %d", &stackNum, &value);
                add(ms, stackNum, value);
                break;
            case 2:
                printf("Enter stack number (0-%d): ", n-1);
                scanf("%d", &stackNum);
                delete(ms, stackNum);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 3);

    freeMultiStack(ms);
    return 0;
}