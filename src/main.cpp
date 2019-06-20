#include "Header.h"

int Memory[100];
int sc_FlagRegister = 0;
keys key;

int main(int argc, char *argv[])
{
	setbuf(stdout, NULL); // SAMAYA VAZHNAY CHTOB IO FUNKCIA!!!
	mt_clrscr();
	sc_regInit();
	sc_memoryInit();
	InitBigSymbolDB();
	InitKeyDB();
	if (ReadAssemblerFile(argc, argv) == -1)
		return -1;
	PrintInterface();
	while(key != Quit)
	{
		rk_readkey(&key);
		SimpleCommand(key);
	}
	return 0;
}

