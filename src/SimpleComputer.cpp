#include "Header.h"

int Memory[100];
int sc_FlagRegister = 0;

int main()
{
	sc_memoryInit();
	sc_memorySet(0, 21);
	char Mem[] = "Mem";
	sc_memorySave(Mem);
	sc_memorySet(1, 43);
	sc_memorySet(-1, 63);
	sc_memorySet(101, 63);
	PrintMem();
	sc_memoryLoad(Mem);
	std::cout << std::endl;
	PrintMem();
	int value;
	sc_regGet(1, &value);
	std::cout << std::endl << value;
	sc_regSet(1, 0);
	sc_regGet(1, &value);
	std::cout << " " << value << " Memory overflow flag + set flag" << std::endl;
	int Com = 0, Oper = 0;
	sc_commandDecode(2076, &Com, &Oper);
	std::cout << "Command " << Com << " " << "Operand " << Oper << std::endl;
	sc_commandDecode(200, &Com, &Oper);
	sc_regGet(2, &value);
	std::cout << "Incorrect command flag " << value << std::endl;
	sc_commandEncode(Com, Oper, &value);
	std::cout << "Value " << value << std::endl;
	sc_regSet(1, 3);
	sc_regSet(3, 1);
	sc_regGet(3, &value);
	std::cout << "Incorrect flag value " << value << std::endl;
}
