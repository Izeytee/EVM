#include "Header.h"

int sc_regSet(int sc_register, int value)
{
	if (sc_register > 0 && sc_register < 6)
	{
		if (value == 1)
		{
			sc_FlagRegister |= (1 << (sc_register - 1));
			CheckFlags();
			return 0;
		}
		if (value == 0)
		{
			sc_FlagRegister &= (~(1 << (sc_register - 1)));
			CheckFlags();
			return 0;
		}
		return -1;
	}
	else
		return -1;
}

int sc_regGet(int sc_register, int *value)
{
	if (sc_register > 0 && sc_register < 6)
	{
		*value = (sc_FlagRegister >> (sc_register - 1)) & 0x1;
		return 0;
	}
	else
		return -1;	
}

int sc_commandEncode(int command, int operand, int *value)
{
	if (command < 0 || command > 127 || operand < 0 || operand > 127)
		return -1;
	*value = command;
	*value <<= 7;
	*value |= operand;
	return 0;
}

int sc_commandDecode(int value, int * command, int * operand)
{
	std::string Input;
	Convert10to2(value, &Input);
	std::string Oper = "", Com = "";
	Oper.replace(0, 7, Input, 8, 15);
	Com.replace(0, 7, Input, 1, 7);
	Convert2to10(Oper, operand);
	Convert2to10(Com, command);
	if (!CheckCommand(value))
		return -1;
	return 0;
}

int sc_memoryInit(void)
{
	for (int i = 0; i < 100; i++)
		Memory[i] = 0;
	return 0;
}

int sc_memorySet(int address, int value)
{
	if (address < 100 && address >= 0 && value >= 0 && value <= 32767)
	{
		Memory[address] = value;
		return 0;
	}
	else
	{
		sc_regSet(MemoryOverFlow, 1);
		return -1;
	}
}

int sc_memoryGet(int address, int *value)
{
	if (address < 100 && address >= 0)
	{
		*value = Memory[address];
		return 0;
	}
	else
	{
		sc_regSet(MemoryOverFlow, 1);
		return -1;
	}
}

int sc_memorySave(char *filename)
{
	int fd = creat(filename, S_IRWXU);
	if (fd == -1)
	{
		return -1;
	}
	write(fd, (char*)Memory, sizeof(Memory));
	close(fd);
	return 0;
}

int sc_memoryLoad(char *filename)
{
	int fd = open(filename, O_RDONLY);
	if (fd == -1)
		return -1;
	read(fd, (char*)Memory, sizeof(Memory) );
	close(fd);
	return 0;
}

int sc_regInit(void)
{
	sc_FlagRegister = 0;
	return 0;
}
