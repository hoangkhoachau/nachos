// exception.cc
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.
#pragma GCC diagnostic ignored "-Wwrite-strings"
#include "copyright.h"
#include "syscall.h"
#include "system.h"
#include <cstring>
#define MAX_READ_STRING_LENGTH 255

//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2.
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions
//	are in machine.h.
//----------------------------------------------------------------------

void AdvancePC() {
    machine->registers[PrevPCReg] = machine->registers[PCReg];
    machine->registers[PCReg] = machine->registers[NextPCReg];
    machine->registers[NextPCReg] += 4;
}

// Input: Khong gian dia chi User(int) - gioi han cua buffer(int)
// Output: Bo nho dem Buffer(char*)
// Chuc nang: Sao chep vung nho User sang vung nho System
char *User2System(int virtAddr, int limit) {
    int i; // chi so index
    int oneChar;
    char *kernelBuf = NULL;
    kernelBuf = new char[limit + 1]; // can cho chuoi terminal
    if (kernelBuf == NULL)
        return kernelBuf;

    memset(kernelBuf, 0, limit + 1);

    for (i = 0; i < limit; i++) {
        machine->ReadMem(virtAddr + i, 1, &oneChar);
        kernelBuf[i] = (char)oneChar;
        if (oneChar == 0)
            break;
    }
    return kernelBuf;
}

// Input: Khong gian vung nho User(int) - gioi han cua buffer(int) - bo nho dem
// buffer(char*) Output: So byte da sao chep(int) Chuc nang: Sao chep vung nho
// System sang vung nho User
int System2User(int virtAddr, int len, char *buffer) {
    if (len < 0)
        return -1;
    if (len == 0)
        return len;
    int i = 0;
    int oneChar = 0;
    do {
        oneChar = (int)buffer[i];
        machine->WriteMem(virtAddr + i, 1, oneChar);
        i++;
    } while (i < len && oneChar != 0);
    return i;
}

void reverse(char src[], int start, int end) {
    while (start < end) {
        char temp =
            src[start]; // a l  => temp = a,   a = l -> l, l = temp = a -> a
        src[start] = src[end];
        src[end] = temp;
        start++;
        end--;
    }
}

// Doc chuoi ki tu:
void readString(char *buffer, int length) {
    gSynchConsole->Read(buffer,
                        length); // dung synchcons de doc du lieu tu nguoi dung
    int addr;
    addr = machine->ReadRegister(4);   // doc thanh ghi thu 4
    System2User(addr, length, buffer); // chuyen du lieu tu system den user
}

// In chuoi ki tu:
void printString(char *buffer) {
    int length = 0;
    while (buffer[length] != '\0')
        length++; // kiem tra so luong ki tu chuoi, den ki tu \0 thi dung
    gSynchConsole->Write(buffer, length + 1); // in ra man hinh console
}

void ExceptionHandler(ExceptionType which) {
    int type = machine->ReadRegister(2);
    switch (which) {
    case NoException: // return control to kernel
        return;
    case PageFaultException:
        printf("Page Fault Exception!\n");
        DEBUG('a',"Page Fault Exception!\n");
        interrupt->Halt();
    case ReadOnlyException:
        printf("Read Only Exception!\n");
        DEBUG('a',"Read Only Exception!\n");
        interrupt->Halt();
    case BusErrorException:
        printf("Bus Error Exception!\n");
        DEBUG('a',"Bus Error Exception!\n");
        interrupt->Halt();
    case AddressErrorException:
        printf("Address Error Exception!\n");
        DEBUG('a',"Address Error Exception!\n");
        interrupt->Halt();
    case OverflowException:
        printf("Overflow Exception!\n");
        DEBUG('a',"Overflow Exception!\n");
        interrupt->Halt();
    case IllegalInstrException:
        printf("Illegal Instruction Exception!\n");
        DEBUG('a',"Illegal Instruction Exception!\n");
        interrupt->Halt();
    case NumExceptionTypes:
        printf("Number Exception!\n");
        DEBUG('a',"Number Exception!\n");
        /* DEBUG('a', which, "\n"); */
        interrupt->Halt();

    case SyscallException:
        switch (type) {
        case SC_Halt: {
            // DEBUG('a', "Shutdown, initiated by user program.\n");
            // printf("Unexpected user mode exception %d %d\n", which, type);
            interrupt->Halt();
        }
        case SC_ReadInt: {
            int maxBuf = 255;
            char *buf = new char[maxBuf + 1];
            bool isNegative = false;
            int start = 0, size, ans = 0;

            size = gSynchConsole->Read(buf, maxBuf);

            // empty input
            if (size == 0) {

                machine->WriteRegister(2, 0);
                AdvancePC();
                delete buf;
                return;
            }

            while (buf[start] == ' ') {
                start++;
            }

            // number is negative
            if (buf[start] == '-') {
                isNegative = true;
                start++;
            }

            // handle: 000005
            while (buf[start] == '0') {
                start++;
            }

            for (int i = start; i < size; ++i) {

                if (buf[i] == '.') { // valid: 1.0000
                    for (int j = i + 1; j < size; ++j) {
                        if (buf[j] != '0') { // Invalid: 1.0002
                            machine->WriteRegister(2, 0);
                            AdvancePC();
                            delete buf;
                            return;
                        }
                    }
                    break;
                } else if (buf[i] < '0' || buf[i] > '9') { // Invalid: 12a1
                    machine->WriteRegister(2, 0);
                    AdvancePC();
                    delete buf;
                    return;
                } else {
                    ans = ans * 10 + (buf[i] - '0');

                    if ((!isNegative && (i - start + 1) > 10) ||
                        (isNegative && (i - start + 1) > 11)) {
                        ans = isNegative ? -__INT_MAX__ : __INT_MAX__;
                        machine->WriteRegister(2, ans);
                        AdvancePC();
                        delete buf;
                        return;
                    }
                }
            }

            if (isNegative)
                ans *= -1;

            machine->WriteRegister(2, ans);
            AdvancePC();
            delete buf;
            return;
        } break;

        case SC_PrintInt: {
            int number = machine->ReadRegister(4);

            if (number == 0) {
                gSynchConsole->Write("0", 1);
                AdvancePC();
                break;
            }

            int maxBuf = 11;
            char *buf = new char[maxBuf + 1];
            bool isNegative = false;
            int start = 0;

            if (number < 0) {
                isNegative = true;
                number *= -1;
                buf[start++] = '-'; // buf[0] = '-'
            }

            while (number != 0) {
                buf[start++] = (number % 10) + '0';
                number /= 10;
            }

            buf[start] = '\0';

            reverse(buf, (isNegative ? 1 : 0), start - 1);

            gSynchConsole->Write(buf, start);
            AdvancePC();
        } break;

        case SC_ReadChar: {

            char c;
            gSynchConsole->Read(&c, 1);
            machine->WriteRegister(2, c); // doc dia chi cua chuoi
            AdvancePC();
        } break;
        case SC_PrintChar: {
            char c = machine->ReadRegister(4); // doc dia chi cua chuoi
            gSynchConsole->Write(&c, 1);
            AdvancePC();
        } break;

        case SC_ReadString: {
            int addr = machine->ReadRegister(4);   // doc dia chi cua chuoi
            int length = machine->ReadRegister(5); // doc do dai cua chuoi
            if (length > MAX_READ_STRING_LENGTH ||
                length <= 0) { // kiem tra do dai cua chuoi
                /* DEBUG(dbgSys, "String length exceeds " <<
                 * MAX_READ_STRING_LENGTH); */
                // printf("OKK");
                interrupt->Halt();
            }
            char *buffer = User2System(addr, length);
            readString(buffer, length);
            delete[] buffer;
            AdvancePC();
        } break;
        case SC_PrintString: {
            int addr = machine->ReadRegister(4); // doc dia chi cua chuoi
            char *buffer = User2System(addr, MAX_READ_STRING_LENGTH);
            printString(buffer);
            AdvancePC();
            delete[] buffer;
        } break;
	case SC_Join:
		{       
			// int Join(SpaceId id)
			// Input: id dia chi cua thread
			// Output: 
			int id = machine->ReadRegister(4);
			
			int res = pTab->JoinUpdate(id);
			
			machine->WriteRegister(2, res);
			IncreasePC();
			return;
		}
		case SC_Exit:
		{
			//void Exit(int status);
			// Input: status code
			int exitStatus = machine->ReadRegister(4);

			if(exitStatus != 0)
			{
				IncreasePC();
				return;
				
			}			
			
			int res = pTab->ExitUpdate(exitStatus);
			//machine->WriteRegister(2, res);

			currentThread->FreeSpace();
			currentThread->Finish();
			IncreasePC();
			return; 
				
		}
        case SC_CreateSemaphore:
		{
			// int CreateSemaphore(char* name, int semval).
			int virtAddr = machine->ReadRegister(4);
			int semval = machine->ReadRegister(5);

			char *name = User2System(virtAddr, MaxFileLength + 1);
			if(name == NULL)
			{
				DEBUG('a', "\n Not enough memory in System");
				printf("\n Not enough memory in System");
				machine->WriteRegister(2, -1);
				delete[] name;
				AdvancePC();
				return;
			}
			
			int res = semTab->Create(name, semval);

			if(res == -1)
			{
				DEBUG('a', "\n Khong the khoi tao semaphore");
				printf("\n Khong the khoi tao semaphore");
				machine->WriteRegister(2, -1);
				delete[] name;
				AdvancePC();
				return;				
			}
			
			delete[] name;
			machine->WriteRegister(2, res);
			AdvancePC();
			return;
		}
			

        default:
            AdvancePC();
            break;
        }
    default:
        break;
    }
}
