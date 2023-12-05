
#include "syscall.h"

int main() {
	char* str;	
	int num;
	PrintString("Enter string length: ");
	num = ReadInt();
    	PrintString("Enter any string: ");
    	ReadString(str, num);
	PrintString("Your string: ");
    	PrintString(str);
	PrintString("\n");
    	Halt();
}
