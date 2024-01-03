#include "syscall.h"
#include "copyright.h"

int main(){
    int i;
    for (i=0;i<100;i++){
        Wait("s1");
        PrintString("B");
        Signal("s");
        }
    return 0;
}