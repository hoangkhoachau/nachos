

#include "syscall.h"


#define MAX_SIZE 100
int A[MAX_SIZE]; 
int main() {
    int n, i, j, tmp;
    
    //PrintString("Enter n: ");
    n = ReadInt();
    //PrintString("You have enter: ");
    //PrintInt(n);
    //PrintString("\n");

    
    for (i = 0; i < n; i++) {
       // PrintString("A[");
        PrintInt(i);
        //PrintString("] = ");

        A[i] = ReadInt();
       
    }

    //PrintString("\nYou have enter:\n");
    for (i = 0; i < n; i++) {
        PrintInt(A[i]);
        //PrintChar('\t');
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < (n - i - 1); j++)
            if (A[j] > A[j + 1]) {
                tmp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = tmp;
            }
    }

    //PrintString("\nAfter sort:\n");
    for (i = 0; i < n; i++) {
        PrintInt(A[i]);
        //PrintChar('\t');
    }
    //PrintChar('\n');

    Halt();
}