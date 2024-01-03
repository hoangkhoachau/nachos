#include "syscall.h"
#include "copyright.h"

int main(){
    int a,b;
    CreateSemaphore("s",1);
    CreateSemaphore("s1",0);
    a=Exec("./printA");
    b=Exec("./printB");
    Join(a);
    Join(b);
    return 0;
}