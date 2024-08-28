#include <stdio.h>
#include <math.h>

#define MAX_SIZE 100

typedef struct {
    int st[MAX_SIZE];
    int tos;
} Stack;

Stack push(Stack s, int x) {
    if (s.tos < MAX_SIZE - 1) {
        s.tos++;
        s.st[s.tos] = x;
    } else {
        printf("Stack overflow\n");
    }
    return s;
}

long convert(Stack s) {
    long n = 0;
    int i;
    for (i = s.tos; i >= 0; i--) {
        n = n * 10 + s.st[i];
    }
    return n;
}

void convertDec(Stack s, int str[MAX_SIZE]) {
    int i;
    for (i = 0; i <= s.tos; i++) {
        str[i] = s.st[i];
    }
}

int main() {
    Stack s = {.tos = -1};
    Stack s2 = {.tos = -1};
    int n, i;
    double num, dn;
    
    printf("Enter a decimal number: ");
    if (scanf("%lf", &num) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    n = (int)num;
    
    // Integer part
    if (n == 0) {
        s = push(s, 0);
    } else {
        while (n > 0) {
            s = push(s, (n % 2));
            n = n / 2;
        }
    }

    // Decimal part
    dn = num - (int)num;
    
    if (dn != 0) {
        int precision = 0;
        while (dn != 0 && precision < MAX_SIZE) {
            dn *= 2;
            s2 = push(s2, (int)dn);
            dn -= (int)dn;
            precision++;
        }
    }

    long bin = convert(s);
    int binDec[MAX_SIZE];
    convertDec(s2, binDec);

    printf("The number in binary is: %ld", bin);
    if (s2.tos >= 0) {
        printf(".");
        for (i = 0; i <= s2.tos; i++) {
            printf("%d", binDec[i]);
        }
    }
    printf("\n");

    return 0;
}