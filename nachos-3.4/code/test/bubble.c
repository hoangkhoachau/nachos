

#include "syscall.h"


#define MAX_SIZE 100
int A[MAX_SIZE]; 
int main() {
    int n, i, j, temp;
    
    PrintString("Input n: ");
    n = ReadInt();
    PrintString("You have n: ");
    PrintInt(n);
    PrintString("\n");

    
    for (i = 0; i < n; i++) {
       PrintString("A[");
        PrintInt(i);
        PrintString("] = ");
        A[i] = ReadInt();   
    }
    PrintString("\n");

    PrintString("Array:\n");
    for (i = 0; i < n; i++) {
        PrintInt(A[i]);
        //PrintChar('\t');
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < (n - i - 1); j++)
            if (A[j] > A[j + 1]) {
                temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
            }
    }

    PrintString("\n");
    PrintString("Array after sort:\n");
    for (i = 0; i < n; i++) {
        PrintInt(A[i]);
        PrintChar('\t');
    }
    PrintString("\n");

    Halt();
}