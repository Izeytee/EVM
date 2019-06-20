#include "Header.h"

BigSymbol BSDB[19];
KeyCode KCDB[13];
char Memoryfilename[21];
int BigSymbol[2];

int Accumulator;
int CurrentMemoryAddress;

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
	for (unsigned int i = 0; i < Origin.length(); i++)
		if (Origin[i] == '1')
		{
			for (unsigned int j = 0; j < Origin.length() - 1 - i; j++, Summand *= 2)
				;
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
	for (unsigned int i = Origin.length(); i > 0; i--)
	{
		Num.resize(Num.length() + 1);
		for (unsigned int j = Num.length() - 1; j > 0; j--)
			Num[j] = Num[j - 1];
		Num[0] = Origin[i - 1];
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
}

void Convert16to2(std::string Origin, std::string *Result)
{
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

void InitBigSymbolDB(void)
{
	BSDB[0].Symbol = '0';
	BSDB[0].Cells[0] = 1111630872;
	BSDB[0].Cells[1] = 405029442;	
	BSDB[1].Symbol = '1';
	BSDB[1].Cells[0] = 269752336;
	BSDB[1].Cells[1] = 2081427472;
	BSDB[2].Symbol = '2';
	BSDB[2].Cells[0] = 541213244;
	BSDB[2].Cells[1] = 2114193424;
	BSDB[3].Symbol = '3';
	BSDB[3].Cells[0] = 809517628;
	BSDB[3].Cells[1] = 1010974784;	
	BSDB[4].Symbol = '4';
	BSDB[4].Cells[0] = 606613536;
	BSDB[4].Cells[1] = 1881177634;	
	BSDB[5].Symbol = '5';
	BSDB[5].Cells[0] = 1040319102;
	BSDB[5].Cells[1] = 1044398144;	
	BSDB[6].Symbol = '6';
	BSDB[6].Cells[0] = 1040335420;
	BSDB[6].Cells[1] = 1010975298;
	BSDB[7].Symbol = '7';
	BSDB[7].Cells[0] = 541081726;
	BSDB[7].Cells[1] = 134744080;	
	BSDB[8].Symbol = '8';
	BSDB[8].Cells[0] = 1010975292;
	BSDB[8].Cells[1] = 1010975298;	
	BSDB[9].Symbol = '9';
	BSDB[9].Cells[0] = 1111638588;
	BSDB[9].Cells[1] = 1010974844;		
	BSDB[10].Symbol = 'A';
	BSDB[10].Cells[0] = 606348312;
	BSDB[10].Cells[1] = 1111638654;
	BSDB[11].Symbol = 'B';
	BSDB[11].Cells[0] = 1044529726;
	BSDB[11].Cells[1] = 1044529730;	
	BSDB[12].Symbol = 'C';
	BSDB[12].Cells[0] = 37896764;
	BSDB[12].Cells[1] = 1010975234;	
	BSDB[13].Symbol = 'D';
	BSDB[13].Cells[0] = 1111638590;
	BSDB[13].Cells[1] = 1044529730;	
	BSDB[14].Symbol = 'E';
	BSDB[14].Cells[0] = 2114060926;
	BSDB[14].Cells[1] = 2114060802;	
	BSDB[15].Symbol = 'F';
	BSDB[15].Cells[0] = 2114060926;
	BSDB[15].Cells[1] = 33686018;	
	BSDB[16].Symbol = '+';
	BSDB[16].Cells[0] = 2115508224;
	BSDB[16].Cells[1] = 1579134;	
	BSDB[17].Symbol = ' ';
	BSDB[17].Cells[0] = 0;
	BSDB[17].Cells[1] = 0;	
	BSDB[18].Symbol = '-';
	BSDB[18].Cells[0] = 2113929216;
	BSDB[18].Cells[1] = 126;	
}

void InitKeyDB(void)
{
	KCDB[0].KeyCommand = "\E[A";
	KCDB[0].key = Up;
	KCDB[1].KeyCommand = "\E[C";
	KCDB[1].key = Right;
	KCDB[2].KeyCommand = "\E[B";
	KCDB[2].key = Down;
	KCDB[3].KeyCommand = "\E[D";
	KCDB[3].key = Left;
	KCDB[4].KeyCommand = "l";
	KCDB[4].key = Load;
	KCDB[5].KeyCommand = "s";
	KCDB[5].key = Save;
	KCDB[6].KeyCommand = "r";
	KCDB[6].key = Run;
	KCDB[7].KeyCommand = "t";
	KCDB[7].key = Step;
	KCDB[8].KeyCommand = "\E[15~";
	KCDB[8].key = F5;
	KCDB[9].KeyCommand = "\E[17~";
	KCDB[9].key = F6;
	KCDB[10].KeyCommand = "q";
	KCDB[10].key = Quit;
	KCDB[11].KeyCommand = "i";
	KCDB[11].key = Reset;
	KCDB[12].KeyCommand = "e";
	KCDB[12].key = Enter;
}

int IdentifyCells(char Symbol, int *Cells)
{
	int i = 0;
	while (Symbol != BSDB[i].Symbol && i < 19)
		i++;
	if (i == 19)
		return -1;
	Cells[0] = BSDB[i].Cells[0];
	Cells[1] = BSDB[i].Cells[1];
	return 0;
}

int IdentifyKey(std::string KeyCommand, enum keys *key)
{
	int i;
	for (i = 0; KeyCommand != KCDB[i].KeyCommand && i < 13; i++)
		;
	if (i == 13)
	{
		(*key) = WrongKey;
		return -1;
	}
	(*key) = KCDB[i].key;
	return 0;
}

void UpdateMemoryLocation(enum colors FC, enum colors BC, int MemAddress)
{
	int val;
	std::string valS;
	mt_setfgcolor(FC);
	mt_setbgcolor(BC);
	mt_gotoXY((MemAddress % 5) * 8  + 2, MemAddress / 5 + 2);
	sc_memoryGet(MemAddress, &val);
	Convert10to16(val, &valS);
	val <= 0x3FFF ? std::cout << '+' : std::cout << ' ';
	std::cout << valS;
	mt_setfgcolor(Standart);
	mt_setbgcolor(Standart);
	PrintInstructionCounter();
	PrintAccumulator();
	mt_gotoXY(1, 23);
}

bool CheckCommand(int value)
{
	std::string Res;
	Convert10to2(value, &Res);
	Res.erase(8, 16);
	Res.erase(0, 1);
	Convert2to10(Res, &value);
	if ((value >= 0x10 && value <= 0x11) || (value >= 0x20 && value <= 0x21)
	|| (value >= 0x30 && value <= 0x33) || (value >= 0x40 && value <= 0x43)
	|| (value >= 0x51 && value <= 0x59) || (value >= 0x60 && value <= 0x69)
	|| (value >= 0x70 && value <= 0x76))
		return true;
	return false;
	
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

void PrintMem(void)
{
	int val;
	std::string valS;
	for (int i = 0; i < 20; i++)
	{
		mt_gotoXY(2, i + 2);
		for (int j = 0; j < 5; j++)
		{
			mt_gotoXY(j*8 + 2, i + 2);
			sc_memoryGet(j + i*5, &val);
			val <= 0x3FFF ? std::cout << '+' : std::cout << ' ';
			Convert10to16(val, &valS);
			std::cout << valS;
		}
	}
}

char identifyFlag(int value)
{
	switch (value)
	{
		case 1:
			return 'M';
		case 2:
			return 'C';
		case 3:
			return 'D';
		case 4:
			return 'I';
		case 5:
			return 'O';
		default:
			return -1;
	}
}

void PrintBigSymbols(int address)
{
	int val;
	std::string valS;
	sc_memoryGet(address, &val);
	char c;
	Convert10to16(val, &valS);
	c = val < 0x3FFF ? '+' : ' ';
	IdentifyCells(c, BigSymbol);
	bc_printbigchar(BigSymbol, 44, 14, Yellow, Black);
	for(int i = 1; i <= 4; i++)
	{
		c = valS[i - 1];
		IdentifyCells(c, BigSymbol);
		bc_printbigchar(BigSymbol, 44 + i * 8, 14, Yellow, Black);
	}
	mt_gotoXY(1, 23);
}

void CheckFlags(void)
{
	int val;
	char c;
	for (int i = 1; i < 6; i++)
	{
		sc_regGet(i, &val);
		c = identifyFlag(i);
		mt_gotoXY(68 + 2*i, 5);
		if (val)
			mt_setfgcolor(Red);
		else
			mt_setfgcolor(Black);
		std::cout << c;
	}
	mt_setfgcolor(Standart);
	mt_setbgcolor(Standart);
	mt_gotoXY(1, 23);
}

void GetBigNumber(std::string origin, int *A)
{
	char c;
	int *B = new int[2];
	for(int i = 0; i < 5; i++)
	{
		c = origin[i];
		IdentifyCells(c, B);
		for(int j = 0; j < 2; j++)
			A[i * 2 + j] = B[j];
	}
}

void ChangeMemValue(void)
{
	int Value;
	std::cin >> Value;
	sc_memorySet(CurrentMemoryAddress, Value);
	PrintBigSymbols(CurrentMemoryAddress);
	std::cout << "                                 ";
	UpdateMemoryLocation(Green, White);
}

void ChangeAccumValue(void)
{
	std::cin >> Accumulator;
	if (Accumulator > 32767 || Accumulator < -32767)
	{
		Accumulator = 0;
		sc_regSet(FlagAccumulatorOvervlow, 1);
	}
	mt_gotoXY(1, 23);
	std::cout << "                                 ";
	PrintAccumulator();
}

int ReadAssemblerFile(int argc, char *argv[])
{
	int address, command, operand, value;
	if (argc == 1)
		return 0;
	std::string FP = "Translators/";
	FP += *++argv;
	char *FilePath = new char[FP.length() + 1];
	for (size_t i = 0; i < FP.length(); i++)
		FilePath[i] = FP[i];
	FilePath[FP.length()] = '\0';
	std::ifstream InputFile(FilePath, std::ios::in | std::ios::binary);
	if (!InputFile)
	{
		std::cout << "Incorrect file name";
		return -1;
	}
	while(InputFile.read((char*)&address, sizeof(address)))
	{
		InputFile.read((char*)&command, sizeof(command));		
		InputFile.read((char*)&operand, sizeof(operand));
		command != 1 ? sc_commandEncode(command, operand, &value) : value = operand;
		sc_memorySet(address, value);
	}
	InputFile.close();
	return 0;
}

void PrintOperation(void)
{
	mt_gotoXY(51, 5);
	std::cout << "        ";
	mt_gotoXY(51, 5);
	int value, command, operand;
	sc_memoryGet(CurrentMemoryAddress, &value);
	sc_commandDecode(value, &command, &operand) == -1 ? std::cout << " " : std::cout << "+";
	std::cout << std::hex << command << " : " << operand << std::dec;
	mt_gotoXY(1, 23);
}

void ChangeMemAddress(int Address)
{
	UpdateMemoryLocation(Standart, Standart);
	Address >=0 && Address <= 99 ? CurrentMemoryAddress = Address : sc_regSet(MemoryOverFlow, 1);
	PrintBigSymbols(CurrentMemoryAddress);
	std::cout << "                                 ";
	UpdateMemoryLocation(Green, White);
	PrintOperation();
}

void PrintInstructionCounter(void)
{
	mt_gotoXY(72, 2);
	std::string MemAddressX16;
	Convert10to16(CurrentMemoryAddress, &MemAddressX16);
	std::cout << '+' << MemAddressX16;
	mt_gotoXY(1, 23);
}

void PrintAccumulator(void)
{
	mt_gotoXY(52, 2);
	int sign;
	Accumulator < 0 ? sign = -1 : sign = 1;
	Accumulator >= 0 ? Accumulator < 0x3FFF ? std::cout << '+' : std::cout << ' ' : std::cout << '-';
	std::string AccumValueX16;
	Convert10to16(Accumulator * sign, &AccumValueX16);
	std::cout << AccumValueX16;
	mt_gotoXY(1, 23);
}

void PrintInterface(void)
{
	bc_box(1, 42, 1, 22);
	mt_gotoXY(19, 1);
	std::cout << "Memory";
	bc_box(43, 64, 1, 3);
	mt_gotoXY(49, 1);
	std::cout << "Accumulator";
	bc_box(65, 84, 1, 3);
	mt_gotoXY(66, 1);
	std::cout << "InstructionCounter";
	bc_box(43, 64, 4, 6);
	mt_gotoXY(50, 4);
	std::cout << "Operation";
	bc_box(65, 84, 4, 6);
	mt_gotoXY(72, 4);
	std::cout << "Flags";
	bc_box(43, 84, 7, 12);
	mt_gotoXY(44, 8);
	std::cout << "e - Enter";
	mt_gotoXY(44, 9);
	std::cout << "s - Save";
	mt_gotoXY(44, 10);
	std::cout << "l - Load";
	mt_gotoXY(44, 11);
	std::cout << "r - Run";
	mt_gotoXY(60, 8);
	std::cout << "t - Step";
	mt_gotoXY(60, 9);
	std::cout << "i  - Reset";
	mt_gotoXY(60, 10);
	std::cout << "F5 - Accumulator";
	mt_gotoXY(60, 11);
	std::cout << "F6 - InsrutctionCounter";
	mt_gotoXY(44, 7);
	std::cout << "Keys";
	bc_box(43, 84, 13, 22);
	PrintMem();
	CurrentMemoryAddress = 0;
	Accumulator = 0;
	PrintAccumulator();
	PrintOperation();
	UpdateMemoryLocation(Green, White);
	CheckFlags();
	PrintBigSymbols(CurrentMemoryAddress);
}

int SimpleCommand(enum keys key)
{
	int FlagValue, Address;;
	sc_regGet(FlagIgnoreClockPulse, &FlagValue);
	if (FlagValue == true && key != Reset)
		return -1;
	switch (key)
	{
		case Up:
			if (CurrentMemoryAddress - 5 >= 0)
			{
				UpdateMemoryLocation(Standart, Standart);
				CurrentMemoryAddress -= 5;
				UpdateMemoryLocation(Green, White);
				PrintOperation();
				PrintBigSymbols(CurrentMemoryAddress);
			}
			return 0;
		case Right:
			if ((CurrentMemoryAddress % 5) != 4)
			{
				UpdateMemoryLocation(Standart, Standart);
				CurrentMemoryAddress++;
				UpdateMemoryLocation(Green, White);
				PrintOperation();
				PrintBigSymbols(CurrentMemoryAddress);
			}
			return 0;
		case Down:
			if (CurrentMemoryAddress + 5 <= 99)
			{
				UpdateMemoryLocation(Standart, Standart);
				CurrentMemoryAddress += 5;
				UpdateMemoryLocation(Green, White);
				PrintOperation();
				PrintBigSymbols(CurrentMemoryAddress);
			}
			return 0;
		case Left:
			if ((CurrentMemoryAddress % 5) != 0)
			{
				UpdateMemoryLocation(Standart, Standart);
				CurrentMemoryAddress--;
				UpdateMemoryLocation(Green, White);
				PrintOperation();
				PrintBigSymbols(CurrentMemoryAddress);
			}
			return 0;
		case Load:
			std::cin >> Memoryfilename;
			if (strlen(Memoryfilename) > 20)
				return - 1;
			sc_memoryLoad(Memoryfilename);
			PrintMem();
			UpdateMemoryLocation(Green, White);
			PrintBigSymbols(CurrentMemoryAddress);
			PrintOperation();
			mt_gotoXY(1, 23);
			std::cout << "                                 ";
			mt_gotoXY(1, 23);
			return 0;
		case Save:
			std::cin >> Memoryfilename;
			if (strlen(Memoryfilename) > 20)
				return -1;
			sc_memorySave(Memoryfilename);
			mt_gotoXY(1, 23);
			std::cout << "                                 ";
			mt_gotoXY(1, 23);
			return 0;
		case Reset:
			Signal();
			return 0;
		case Step:
			signalhandler(SIGALRM);
			alarm(0);
			return 0;
		case Run:
			Timer();
			return 0;
		case Enter:
			ChangeMemValue();
			PrintOperation();
			return 0;
		case F5:
			ChangeAccumValue();
			return 0;
		case F6:
			std::cin >> Address;
			ChangeMemAddress(Address);
			return 0;
		case Quit: // Effect can be seen in main
			return 0;
		default:
			return -1;
	}
	return -1;
}
