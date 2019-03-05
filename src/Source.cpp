#include "Header.h"

int sc_regSet(int sc_register, int value)
{
	if (sc_register > 0 && sc_register < 6)
	{
		if (value == 1)
		{
			sc_FlagRegister = sc_FlagRegister | (1 << (sc_register - 1));
			return NULL;
		}
		if (value == 0)
		{
			sc_FlagRegister = sc_FlagRegister & (~(1 << (sc_register - 1)));
			return NULL;
		}
		return NULL;
	}
	else
	{
		int Flag = FlagIncorrectFlag;
		sc_regSet(Flag, 1);
		return NULL;
	}
}

int sc_regGet(int sc_register, int *value)
{
	if (sc_register > 0 && sc_register < 6)
	{
		*value = (sc_FlagRegister >> (sc_register - 1)) & 0x1;
		return NULL;
	}
	else
		return NULL;
}

int sc_commandEncode(int command, int operand, int *value)
{
	std::string Com, Oper, Val = "t";
	if (command < 0 || command > 255)
	{
		int Flag = FlagIncorrectCommand;
		sc_regSet(FlagIncorrectCommand, 1);
		return NULL;
	}
	if (operand < 0 || operand > 255)
		return NULL;
	Convert10to2(command, &Com);
	Convert10to2(operand, &Oper);
	Com.erase(1, 8);
	Oper.erase(1, 8);
	Val = Com + Oper;
	Convert2to10(Val, value);
	return NULL;
}

int sc_commandDecode(int value, int * command, int * operand)
{
	std::string Input;
	if (!CheckCommand(value))
	{
		int Flag = FlagIncorrectCommand;
		sc_regSet(Flag, 1);
		return NULL;
	}
	Convert10to2(value, &Input);
	std::string Oper = "", Com = "";
	Oper.replace(0, 7, Input, 8, 15);
	Com.replace(0, 7, Input, 1, 7);
	Convert2to10(Oper, operand);
	Convert2to10(Com, command);
	return NULL;
}

int sc_memoryInit(void)
{
	for (int i = 0; i < 100; i++)
		Memory[i] = 0;
	return NULL;
}

int sc_memorySet(int address, int value)
{
	if (address < 100 && address >= 0)
	{
		Memory[address] = value;
		return NULL;
	}
	else
	{
		int Flag = MemoryOverFlow;
		sc_regSet(Flag, 1);
		std::cout << "Error. Memory over flow" << std::endl;
		return NULL;
	}
}

int sc_memoryGet(int address, int *value)
{
	if (address < 100 && address >= 0)
	{
		*value = Memory[address];
		return NULL;
	}
	else
	{
		std::cout << "Error. Memory over flow" << std::endl;
		return NULL;
	}
}

int sc_memorySave(char *filename)
{
	std::ofstream out(filename, std::ios::binary);
	if (!out)
	{
		std::cout << "Error. Wrong path" << std::endl;
		return NULL;
	}
	out.write((char*)&Memory, sizeof(Memory));
	out.close();
	return NULL;
}

int sc_memoryLoad(char *filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (!in)
	{
		std::cout << "Error. Wrong path" << std::endl;
		return NULL;
	}
	in.read((char*)Memory, sizeof(Memory));
	in.close();
	return NULL;
}

int sc_regInit(void)
{
	sc_FlagRegister = 0;
	return NULL;
}
