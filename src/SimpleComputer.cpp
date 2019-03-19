#include "Header.h"

int Memory[100];
int sc_FlagRegister = 0;

int main()
{
	FillInputDatabase();
	std::string T;
	while (1)
	{
		std::cin >> T;
		Input(T);
	}
}

