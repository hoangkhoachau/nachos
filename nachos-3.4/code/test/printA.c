#include "syscall.h"
#include "copyright.h"

int main(){
    int i;
    for (i=0;i<100;i++){
        Wait("s");
        PrintString("A");
        Signal("s1");
        }

    return 0;
}