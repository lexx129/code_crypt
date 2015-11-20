#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
 
// Beginning of printfFunction
void printfFunction(char *szText, int (*f) (const char *,...)){
	char * format = new char[4];
	format[0] = '%';
	format[1] = 's';
	format[2] = '\n';
	format[3] = '\0';
    f(format, szText);
}
// Marks the end of printfFunction
void printfFunctionStub(){}
 
void enc(DWORD dwAddress, DWORD dwSize){
    __asm{
        mov ecx,dwAddress
        add ecx,dwSize
        mov eax,dwAddress
        C_loop:
        xor byte ptr ds:[eax], 0x01
			/*mov byte ptr ds : [eax], bl
			push bl
			call DWORD ptr printf
			pop dl*/
		//	mov dl, byte ptr ds : [eax]
			//mov ah, 2
			//int 21h
        inc eax
        cmp eax,ecx
        jl C_loop;
    }
}


 
int main(){
    DWORD dwPrintFunctionSize = 0, dwOldProtect;
    char *fA = NULL, *fB = NULL;
 
    // Obtain the addresses for the functions so we can calculate size.
    fA = (char *)&printfFunction;
    fB = (char *)&printfFunctionStub;
 
    // Get total function size
    dwPrintFunctionSize = (fB - fA);
     
    // Test the function
   //printfFunction("Hello A!\n");
	void(*f)(char*, int(*)(const char *, ...)) = printfFunction;
	//f("First run \n", printf);
     
    // We need to give ourselves access to modifify data at the given address
    VirtualProtect(fA, dwPrintFunctionSize, PAGE_EXECUTE_READWRITE, &dwOldProtect);
     
  // enc((DWORD)fA, dwPrintFunctionSize); // XOR encrypt the function

   enc((DWORD)fA, dwPrintFunctionSize); // XOR decrypt the function
     
    // Restore the old protection
	VirtualProtect(fA, dwPrintFunctionSize, dwOldProtect,NULL);
 
    // Test the function
	//void (*f)(char*, int(*)(const char *,...)) = printfFunction;
	printf("%d%c%d\n", fA, ' ', fB);
	printf("%d\n", dwPrintFunctionSize);
    f("I'm alive!\n", printf);
	system("PAUSE");
    return 0;
}