/* tapwater.c
 
 */

#include "copyright.h"
#include "syscall.h"
#include "util.h"


int main() {
    int inputFD=Open("input.txt", 1),sharedFD,shared1FD,outputFD;
    int r,n,pos=0,i,studentProcs[100],studentN=0,tapProcs[2],j;
    char bff[100];
    char bff2[10];
    CreateFile("shared.txt");
    CreateFile("shared1.txt");
    CreateFile("output.txt");
    if (inputFD==-1){
        PrintString("Can't open input file\n");
        PrintString("Exitting!");
        return 0;
    }

    CreateSemaphore("getData", 0);
    CreateSemaphore("tap", 2);
    CreateSemaphore("tapDone", 0);
    CreateSemaphore("output", 1);
    CreateSemaphore("studentDone", 0);

    sharedFD=Open("shared.txt", 0);

    Write(toString(bff2,1), strlen(bff2), sharedFD);
    tapProcs[0]=Exec("./taps");
    Wait("getData");
    Seek(0, sharedFD);
    Write(toString(bff2,2), strlen(bff2), sharedFD);
    tapProcs[1]=Exec("./taps");
    Wait("getData");

    PrintString("after dispatch faucet\n");

    r=Read(bff,100,inputFD);
    bff[r]=0;
    n=parseInt(bff, &pos);

    for (i=0;i<n;i++,studentN=0){
        pos++;
        while (bff[pos]&&bff[pos]!='\n'){
            r=parseInt(bff, &pos);        
            Seek(0, sharedFD);
            Write(toString(bff2,r), strlen(bff2), sharedFD);
            studentProcs[studentN++]=Exec("./student");
            Wait("getData");
        }
        PrintString("after dispatch student\n");
        for (j=0;j<studentN;j++)
            Join(studentProcs[j]);
        Wait("output");
        outputFD=Open("output.txt", 0);
        Seek(-1, outputFD);
        Write("\n", 1, outputFD);
        Close(outputFD);
        Signal("output");
    }
    Close(sharedFD);

    shared1FD=Open("shared1.txt", 0);
    Seek(0, shared1FD);
    Write("^ ^", 3, shared1FD);
    Close(shared1FD);
    Signal("studentDone");
    Signal("studentDone");
    Join(tapProcs[0]);
    Join(tapProcs[1]);
    outputFD = Open("output.txt", 0);
    Seek(-5, outputFD);
    Write("    ", 4, outputFD);

    Halt();
    return 0;
}
