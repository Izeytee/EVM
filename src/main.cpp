#include "Header.h"

int Memory[100];
int sc_FlagRegister = 0;
keys key;

int main()
{
	setbuf(stdout, NULL); // SAMAYA VAZHNAY CHTOB IO FUNKCIA!!!
	mt_clrscr();
	sc_regInit();
	sc_memoryInit();
	InitBigSymbolDB();
	InitKeyDB();
	/*int command = 0x10, operand = 12, value;	tests
	sc_commandEncode(command, operand, &value);
	sc_memorySet(0, value);
	command = 0x11;
	sc_commandEncode(command, operand, &value);
	sc_memorySet(1, value);
	command = 0x20;
	operand = 1;
	sc_commandEncode(command, operand, &value);
	sc_memorySet(2, value);
	command = 0x21;
	operand = 50;
	sc_commandEncode(command, operand, &value);
	sc_memorySet(3, value);
	command = 0x30;
	operand = 50;
	sc_commandEncode(command, operand, &value);
	sc_memorySet(4, value);
	command = 0x31;
	operand = 50;
	sc_commandEncode(command, operand, &value);
	sc_memorySet(5, value);
	command = 0x33;
	operand = 50;
	sc_commandEncode(command, operand, &value);
	sc_memorySet(6, value);
	command = 0x32;
	operand = 50;
	sc_commandEncode(command, operand, &value);
	sc_memorySet(7, value);
	command = 0x32;
	operand = 0;
	sc_commandEncode(command, operand, &value);
	sc_memorySet(8, value);*/
	PrintInterface();
	while(key != Quit)
	{
		rk_readkey(&key);
		SimpleCommand(key);
	}
	return 0;
}

