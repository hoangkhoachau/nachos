
#include "syscall.h"

int main() {
    	// PrintChar('\n');
    	char str[255];
	int num = 0;
	PrintString("Enter any number: ");
	num = ReadInt();
	PrintString("Your number: ");
	PrintInt(num);
	PrintString("\n");
    	PrintString("Enter any string: ");
    	ReadString(str, 255);
	PrintString("Your string: ");
    	PrintString(str);
	PrintString("\n");
    	// PrintInt(ReadInt());
    	// PrintChar('\n');
    	Halt();
}
