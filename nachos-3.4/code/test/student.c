/* people.c
 *	Program that helps in solving the tapwater problem in test/tapwater.c.
 *
 *	people will write which person needs water to taps.txt and output.txt.
 
 */

#include "copyright.h"
#include "syscall.h"
#include "util.h"

int main() {
    int sharedFD=Open("shared.txt", 0),outputFD, shared1FD;
    int r,j;
    char bff[100];
    char bff2[100];
    int bottleSize;
    if (sharedFD==-1){
        PrintString("student Can't open shared file\n");
        PrintString("Exitting!");
        return 0;
    }
    if (outputFD==-1){
        PrintString("student Can't open output file\n");
        PrintString("Exitting!");
        return 0;
    }
    if (shared1FD==-1){
        PrintString("student Can't open shared1 file\n");
        PrintString("Exitting!");
        return 0;
    }
    r=Read(bff,100,sharedFD);
    bff[r]=0;
    j=0;
    bottleSize=parseInt(bff, &j);
    Close(sharedFD);
    Signal("getData");
    Wait("tap");
    shared1FD=Open("shared1.txt", 0);
    Write(toString(bff2,bottleSize), 100, shared1FD);
    Close(shared1FD);
    Wait("output");
    outputFD=Open("output.txt", 0);
    Seek(-1, outputFD);
    Write(toString(bff2,bottleSize), strlen(bff2), outputFD);
    Write(" ", 1, outputFD);
    Close(outputFD);
    Signal("output");
    Signal("studentDone");
    PrintInt(bottleSize);
    Wait("tapDone");
    PrintString("-------------exiting student\n");

   
    return 0;
}
