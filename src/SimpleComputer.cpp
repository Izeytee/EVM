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
	PrintInterface();
	while(key != quite)
	{
		rk_readkey(&key);
		SimpleCommand(key);
	}
}

