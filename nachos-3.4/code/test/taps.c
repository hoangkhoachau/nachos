/* taps.c
 *	Program that helps in solving the tapwater problem in test/tapwater.c.
 *
 *	taps will write which tap distributed water to output.txt.
 *
 * 	NOTE: for some reason, user programs with global data structures
 *	sometimes haven't worked in the Nachos environment.  So be careful
 *	out there!  One option is to allocate data structures as
 * 	automatics within a procedure, but if you do this, you have to
 *	be careful to allocate a big enough stack to hold the automatics!
 */

#include "copyright.h"
#include "syscall.h"
#include "util.h"

int main() {
    int sharedFD=Open("shared.txt", 0),outputFD, shared1FD=Open("shared1.txt", 0);
    int r,t,j;
    long i;
    char bff[100];
    char bff2[100];
    int tapNumber;
    if (sharedFD==-1){
        PrintString("taps Can't open shared file\n");
        PrintString("Exitting!");
        return 0;
    }
    if (outputFD==-1){
        PrintString("taps Can't open output file\n");
        PrintString("Exitting!");
        return 0;
    }
    if (shared1FD==-1){
        PrintString("taps Can't open shared1 file\n");
        PrintString("Exitting!");
        return 0;
    }
    r=Read(bff,100,sharedFD);
    bff[r]=0;
    j=0;
    tapNumber=parseInt(bff, &j);
    Close(sharedFD);
    Signal("getData");

    while (1){
        for (i=0;i<200;i++);
        r=Read(bff,100,shared1FD);
        j=0;
        t = parseInt(bff, &j);
        PrintString(bff);
        PrintInt(t);
        if (t<0) break;
        //delete read number from shared1.txt
        Seek(0, shared1FD);
        for (i=0;i<j;i++) Write(" ",1, shared1FD);

        Wait("studentDone");
        Wait("output");
        outputFD=Open("output.txt", 0);
        Seek(-1, outputFD);
        Write(toString(bff2,tapNumber), strlen(bff2), outputFD);
        Write("  ", 1, outputFD);
        Close(outputFD);
        Signal("output");
//        emulate the time it takes to distribute water
        for (i=0;i<1000*t;i++);
        Signal("tap");
        Signal("tapDone");
    }
    PrintString("exiting taaps\n");

    return 0;
}
