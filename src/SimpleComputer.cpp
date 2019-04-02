#include "Header.h"

int Memory[100];
int sc_FlagRegister = 0;

int main()
{
	mt_clrscr();
	sc_regInit();
	sc_memoryInit();
	InitBigSymbolDB();
	PrintInterface();
	int fd = open("BigSymbols", O_WRONLY);
	int A[32];
	int B[32];
	int *n = new int;
	char *C = new char[3];
	C[0] = 'a';
	C[1] = 'b';
	C[2] = 'a';
	std::string test = "0127";
	GetBigNumber(test, A);
	bc_bigcharwrite(fd, A, 4);
	fd = open("BigSymbols", O_RDONLY);
	bc_bigcharread(fd, B, 4, n);
	for (int i = 0; i < 8; i++)
		std::cout << B[i] << " ";
	std::cout << std::endl << *n <<std::endl;
	bc_printA(C);
	bc_getbigcharpos(B, 4, 1, n);
	std::cout << std::endl << *n << std::endl;
	bc_setbigcharpos(B, 4, 1, 0);
	bc_printbigchar(B, 1, 26, Red, White);
}

