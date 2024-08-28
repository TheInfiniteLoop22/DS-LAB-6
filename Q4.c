// Given an array arr with n elements and a number k, k<n. The task is to delete k
// elements which are smaller than next element (i.e., we delete arr[i] if arr[i] <
// arr[i+1]) or become smaller than next because next element is deleted. Example:
// Input: arr[] = {20, 10, 25, 30, 40}, k = 2
// Output: 25 30 40
// Explanation: First we delete 10 because it follows arr[i] < arr[i+1]. Then we delete 20
// because 25 is moved next to it and it also starts following the condition.

#include <stdio.h> 
#include <stdlib.h>

typedef struct {
    int *st;
    int tos;
} Stack;

Stack push(Stack s,int x) {
    s.tos +=1;
    s.st[s.tos] = x;
    return s;
}

Stack del(Stack s,int ind) {
    int i;
    for (i=ind;i<s.tos;i++) {
        s.st[i] = s.st[i+1];
    }
    s.tos-=1;
    return s;
}

int main() {

    Stack s;

    int n,i,j,k,count=0;
    
    printf("Enter number of elements ");
    scanf("%d",&n);

    s.st = (int *) malloc (n * sizeof(int));

    for(i=0;i<n;i++) {
        printf("Enter element no. %d ",(i+1));
        scanf("%d",&s.st[i]);
    }
    s.tos = n-1;

    printf("Enter the number of elements that must be deleted ");
    scanf("%d",&k);


    //one approach
    //compares each element with its successor, and returns to the start of the array everytime an element is deleted
    // while (k > 0) {
    //     for (i=0;i<=s.tos-1;i++) {
    //         if (s.st[i] < s.st[i+1]) {
    //             s = del(s,i);
    //             k-=1;
    //             break;
    //         }
    //     }
    // }


    //another approach 
    //compares the element to the k ones in front of it
    for(i=0;i<=s.tos-k;i++) {
        if (count == k) 
            break;
        for(j=i+1;j<=(i+1)+k;j++) {
            if (s.st[i] < s.st[j]) {
                s = del(s,0);
                count+=1;
            }
        }
    }


    printf("The final array is:\n");
    for(i = 0;i <= s.tos; i++) {
        printf("%d ",s.st[i]);
    }

    return 0;
}