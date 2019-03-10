#include "Header.h"

struct ConverterStrForSwitch{ std::string Str; int index; };

const int index = 2;

ConverterStrForSwitch Database[index];

void FillInputDatabase()
{
	for (int i = 0; i < index; i++)
		Database[i].index = i;
	Database[0].Str = "PrintInterface";
	Database[1].Str = "GraphicsTest";
}

void Convert10to2(int Origin, std::string *Result)
{
	int Multiply = 16384;
	*Result = "";
	while (Multiply >= 1)
	{
		if (Origin - Multiply < 0)
			(*Result).insert((*Result).length(), "0");
		else
		{
			Origin -= Multiply;
			(*Result).insert((*Result).length(), "1");
		}
		Multiply /= 2;
	}
}

void Convert2to10(std::string Origin, int *Result)
{
	*Result = 0;
	int Summand = 1;
	for (int i = 0; i < Origin.length(); i++)
		if (Origin[i] == '1')
		{
			for (int j = 0; j < Origin.length() - 1 - i; j++)
				Summand *= 2;
			*Result += Summand;
			Summand = 1;
		}
}

void InsertSymbolIn16(int Num, std::string *Result)
{
	switch (Num)
	{
	case 0:
		(*Result).insert(0, "0");
		break;
	case 1:
		(*Result).insert(0, "1");
		break;
	case 2:
		(*Result).insert(0, "2");
		break;
	case 3:
		(*Result).insert(0, "3");
		break;
	case 4:
		(*Result).insert(0, "4");
		break;
	case 5:
		(*Result).insert(0, "5");
		break;
	case 6:
		(*Result).insert(0, "6");
		break;
	case 7:
		(*Result).insert(0, "7");
		break;
	case 8:
		(*Result).insert(0, "8");
		break;
	case 9:
		(*Result).insert(0, "9");
		break;
	case 10:
		(*Result).insert(0, "A");
		break;
	case 11:
		(*Result).insert(0, "B");
		break;
	case 12:
		(*Result).insert(0, "C");
		break;
	case 13:
		(*Result).insert(0, "D");
		break;
	case 14:
		(*Result).insert(0, "E");
		break;
	case 15:
		(*Result).insert(0, "F");
		break;
	default:
		std::cout << "Error. Incorrect input symbol";
		return;
	}
}

void Convert2to16(std::string Origin, std::string *Result)
{
	(*Result) = "";
	int NumInt;
	std::string Num = "";
	for (int i = Origin.length() - 1; i >= 0; i--)
	{
		Num.resize(Num.length() + 1);
		for (int j = Num.length() - 1; j > 0; j--)
			Num[j] = Num[j - 1];
		Num[0] = Origin[i];
		if (Num.length() == 4)
		{
			Convert2to10(Num, &NumInt);
			InsertSymbolIn16(NumInt, Result);
			Num = "";
		}
	}
	if (Num.length() > 0)
	{
		Convert2to10(Num, &NumInt);
		InsertSymbolIn16(NumInt, Result);
	}
	(*Result).insert(0, "0x");
}

void Convert16to2(std::string Origin, std::string *Result)
{
	Origin.erase(0, 2);
	(*Result) = "";
	char Current;
	while (Origin.length() > 0)
	{
		Current = Origin[Origin.length() - 1];
		switch (Current)
		{
		case '0':
			(*Result).insert(0, "0000");
			break;
		case '1':
			(*Result).insert(0, "0001");
			break;
		case '2':
			(*Result).insert(0, "0010");
			break;
		case '3':
			(*Result).insert(0, "0011");
			break;
		case '4':
			(*Result).insert(0, "0100");
			break;
		case '5':
			(*Result).insert(0, "0101");
			break;
		case '6':
			(*Result).insert(0, "0110");
			break;
		case '7':
			(*Result).insert(0, "0111");
			break;
		case '8':
			(*Result).insert(0, "1000");
			break;
		case '9':
			(*Result).insert(0, "1001");
			break;
		case 'A':
			(*Result).insert(0, "1010");
			break;
		case 'B':
			(*Result).insert(0, "1011");
			break;
		case 'C':
			(*Result).insert(0, "1100");
			break;
		case 'D':
			(*Result).insert(0, "1101");
			break;
		case 'E':
			(*Result).insert(0, "1110");
			break;
		case 'F':
			(*Result).insert(0, "1111");
			break;
		default:
			std::cout << "Incorrect symbol" << std::endl;
			return;
		}
		Origin.erase(Origin.length() - 1);
	}
}

bool CheckCommand(int value)
{
	std::string Res;
	Convert10to2(value, &Res);
	Res.erase(8, 16);
	Res.erase(0, 1);
	Convert2to10(Res, &value);
	switch (value)
	{
	case 16:
		return true;
	case 17:
		return true;
	case 32:
		return true;
	case 33:
		return true;
	case 48:
		return true;
	case 49:
		return true;
	case 50:
		return true;
	case 51:
		return true;
	case 64:
		return true;
	case 65:
		return true;
	case 66:
		return true;
	case 67:
		return true;
	case 81:
		return true;
	case 82:
		return true;
	case 83:
		return true;
	case 84:
		return true;
	case 85:
		return true;
	case 86:
		return true;
	case 87:
		return true;
	case 88:
		return true;
	case 89:
		return true;
	case 96:
		return true;
	case 97:
		return true;
	case 98:
		return true;
	case 99:
		return true;
	case 100:
		return true;
	case 101:
		return true;
	case 102:
		return true;
	case 103:
		return true;
	case 104:
		return true;
	case 105:
		return true;
	case 112:
		return true;
	case 113:
		return true;
	case 114:
		return true;
	case 115:
		return true;
	case 116:
		return true;
	case 117:
		return true;
	case 118:
		return true;
	default:
		return false;
	}
}

void Convert10to16(int Origin, std::string *Result)
{
	Convert10to2(Origin, Result);
	Convert2to16(*Result, Result);
}

void Convert16to10(std::string Origin, int *Result)
{
	Convert16to2(Origin, &Origin);
	Convert2to10(Origin, Result);
}

void PrintInterface(void)
{
	std::string res = "";
	int k = 4;
	std::cout << "\u250C";
	for (int i = 1; i < k * 4; i++)
		std::cout << "\u2500";
	std::cout << "Memory";
	for (int i = 0; i < k * 4; i++)
		std::cout << "\u2500";
	std::cout << "\u2500\u2500\u2510";
	std::cout << "\u250C\u2500\u2500\u2500 Accumulator\u2500\u2500\u2500\u2510";
	std::cout << "\u250C InstructionCounter\u2510";
	std::cout << std::endl << "\u2502";
	for (int i = 0; i < 5; i++)
	{
		Convert10to16(Memory[i], &res);
		std::cout << res << "\t";
	}
	std::cout << "\u2502\u2502                  \u2502\u2502                   \u2502" << std::endl << "\u2502";
	for (int i = 5; i < 10; i++)
	{
		Convert10to16(Memory[i], &res);
		std::cout << res << "\t";
	}
	std::cout << "\u2502\u2514";
	for (int i = 0; i < 18; i++)
		std::cout << "\u2500";
	std::cout << "\u2518\u2514";
	for (int i = 0; i < 19; i++)
		std::cout << "\u2500";
	std::cout << "\u2518" << std::endl << "\u2502";
	for (int i = 10; i < 15; i++)
	{
		Convert10to16(Memory[i], &res);
		std::cout << res << "\t";
	}

	std::cout << "\u2502";
	std::cout << "\u250C\u2500\u2500\u2500 Operation\u2500\u2500\u2500\u2500\u2500\u2510";
	std::cout << "\u250C\u2500\u2500\u2500\u2500\u2500\u2500 Flags\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2510";
	std::cout << std::endl << "\u2502";

	for (int i = 15; i < 20; i++)
	{
		Convert10to16(Memory[i], &res);
		std::cout << res << "\t";
	}

	std::cout << "\u2502\u2502                  \u2502\u2502                   \u2502" << std::endl << "\u2502";
	for (int i = 20; i < 25; i++)
	{
		Convert10to16(Memory[i], &res);
		std::cout << res << "\t";
	}
	std::cout << "\u2502\u2514";
	for (int i = 0; i < 18; i++)
		std::cout << "\u2500";
	std::cout << "\u2518\u2514";
	for (int i = 0; i < 19; i++)
		std::cout << "\u2500";
	std::cout << "\u2518" << std::endl << "\u2502";

	for (int i = 25; i < 30; i++)
	{
		Convert10to16(Memory[i], &res);
		std::cout << res << "\t";
	}

	std::cout << "\u2502\u250C Keys:\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500";
	std::cout << "\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2510";
	std::cout << std::endl << "\u2502";

	for (int i = 30; i < 50; i++)
	{
		Convert10to16(Memory[i], &res);
		std::cout << res << "\t";
		if (k)
			k--;
		else
		{
			std::cout << "\u2502";
			std::cout << "\u2502                                       \u2502 " << std::endl << "\u2502";
			k = 4;
		}
	}

	for (int i = 50; i < 55; i++)
	{
		Convert10to16(Memory[i], &res);
		std::cout << res << "\t";
	}
	std::cout << "\u2502\u2514";

	for (int i = 0; i < 39; i++)
		std::cout << "\u2500";
	std::cout << "\u2518" << std::endl << "\u2502";

	for (int i = 55; i < 60; i++)
	{
		Convert10to16(Memory[i], &res);
		std::cout << res << "\t";
	}

	std::cout << "\u2502\u250C";
	for (int i = 0; i < 39; i++)
		std::cout << "\u2500";
	std::cout << "\u2510";
	std::cout << std::endl << "\u2502";

	for (int i = 60; i < 100; i++)
	{
		Convert10to16(Memory[i], &res);
		std::cout << res << "\t";
		if (k)
			k--;
		else
		{
			std::cout << "\u2502\u2502";
			for (int j = 0; j < 39; j++)
				std::cout << " ";
			std::cout << "\u2502" << std::endl << "\u2502";
			k = 4;
		}
	}
	std::cout << "\b\u2514";
	for (int i = 0; i < 39; i++)
		std::cout << "\u2500";
	std::cout << "\u2518\u2514";
	for (int i = 0; i < 39; i++)
		std::cout << "\u2500";
	std::cout << "\u2518";
}

void GraphicsTest(void)
{
	int Lines, Columns;
	mt_clrscr();
	mt_gotoXY(5, 10);
	mt_setfgcolor(Red);
	mt_setbgcolor(Black);
	std::cout << "Kirill";
	mt_gotoXY(6, 8);
	mt_setfgcolor(Green);
	mt_setbgcolor(White);
	std::cout << "IP-713";
	mt_gotoXY(10, 1);
	mt_setfgcolor(Standart);
	mt_setbgcolor(Standart);
	mt_getscreensize(&Lines, &Columns);
	std::cout << Lines << std::endl << Columns << std::endl;
}

void Input(std::string Input)
{
	int Check;
	bool l = false;
	for (Check = 0; Check < index; Check++)
		if (Input == Database[Check].Str)
			break;
	switch (Check)
	{
	case 0:
		PrintInterface();
		break;
	case 1:
		GraphicsTest();
		break;
	default:
		std::cout << "Unknown command" << std::endl;
		break;
	}
}
