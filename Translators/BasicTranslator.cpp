#include <iostream>
#include <string>
#include <fstream>

int Address[100];
int AddressIndex, VarIndex;
char Var[100];
std::string GotoAddresses = "";
bool NeedNextString = false, swap = false;

std::ifstream InputFile;
std::ofstream OutputFile;


int FindMemory(std::string Origin)
{
	int ConstVal = 0;
	for (size_t j = 0; j < Origin.length(); ++j)
		ConstVal = ConstVal * 10 + Origin[j];
	for (int i = 99; i > AddressIndex; --i)
		if (ConstVal == Address[i])
			return i;
	Address[VarIndex] = ConstVal;
	while (Origin.length() < 4)
		Origin.insert(0, "0");
	if (VarIndex/10 == 0)
		OutputFile << '0';
	OutputFile << VarIndex << " = +" << Origin << '\n';
	return VarIndex--;
}

int FindVar(char Origin)
{
	for (int i = 99; i > AddressIndex; --i)
		if (Origin == Var[i])
			return i;
	Var[VarIndex] = Origin;
	if (VarIndex/10 == 0)
		OutputFile << '0';
	OutputFile << VarIndex << " = +0000" << '\n';
	return VarIndex--;
}

void IdentifyVal(int *Val, std::string Origin, int index)
{
	if (std::isdigit(Origin[index]))
	{
		std::string StrConstVal;
		size_t j = index;
		if (std::isdigit(Origin[j - 1]))
		{
			while(std::isdigit(Origin[--j]))
				; 
			StrConstVal.assign(Origin, j + 1, index - j);
		}
		else
		{
			while(std::isdigit(Origin[++j]))
				; 
			StrConstVal.assign(Origin, index, j - index);
		}
		
		*Val = FindMemory(StrConstVal);
	}
	else
		*Val = FindVar(Origin[index]);
}

void ExchangeOperation(std::string &Origin, int index, int Number = 0)
{
	int LeftBorder = index - 2, RightBorder = index + 2;
	while (std::isdigit(Origin[--LeftBorder]))
		;
	while (std::isdigit(Origin[++RightBorder]))
		;
	Origin.erase(LeftBorder + 1, RightBorder - LeftBorder - 1);
	std::string InsertChar = "a";
	InsertChar[0] += Number;
	Origin.insert(LeftBorder + 1, InsertChar);
}

void DoSumSub(std::string &Origin)
{
	int Val1, Val2, OperBegin = 0;
	while(!isalnum(Origin[OperBegin++]))
		;
	IdentifyVal(&Val1, Origin, --OperBegin);
	if (AddressIndex / 10 == 0)
		OutputFile << '0';
	OutputFile << AddressIndex++ << " LOAD " << Val1 << '\n';
	for (size_t i = 0; i < Origin.length(); ++i)
		if (Origin[i] == '+' || Origin[i] == '-')
		{
			IdentifyVal(&Val2, Origin, i + 2);
			if (AddressIndex / 10 == 0)
				OutputFile << '0';
			Origin[i] == '+'
				? OutputFile << AddressIndex++ << " ADD " << Val2 << '\n'
				: OutputFile << AddressIndex++ << " SUB " << Val2 << '\n';
		}
}

void DoMultDiv(std::string &Origin, int SavedNumber)
{
	int Val1, Val2;
	for (size_t i = 0; i < Origin.length(); ++i)
		if (Origin[i] == '*' || Origin[i] == '/')
		{
			IdentifyVal(&Val1, Origin, i - 2);
			IdentifyVal(&Val2, Origin, i + 2);
			if (AddressIndex / 10 == 0)
				OutputFile << '0';
			OutputFile << AddressIndex++ << " LOAD " << Val1 << '\n';
			if (AddressIndex / 10 == 0)
				OutputFile << '0';
			Origin[i] == '*'
				? OutputFile << AddressIndex++ << " MUL " << Val2 << '\n'
				: OutputFile << AddressIndex++ << " DIVIDE " << Val2 << '\n';
			if (AddressIndex / 10 == 0)
				OutputFile << '0';
			OutputFile << AddressIndex++ << " STORE " << VarIndex << '\n';
			ExchangeOperation(Origin, i, SavedNumber);
			Var[VarIndex--] = 'a' + SavedNumber++;
			i = 0;
		}
	DoSumSub(Origin);
}

void TranslateCommand(std::string *command, std::string Str)
{
	if (*command == "REM")
		Address[AddressIndex] = 0;
	else if (*command == "INPUT")
	{
		int Var = FindVar(Str[0]);
		if (AddressIndex/10 == 0)
			OutputFile << '0';
		OutputFile << AddressIndex++ << " READ " << Var << '\n';
	}
	else if (*command == "LET")
	{
		int LetVal, SavedNumber = 0;
		std::string Calculation;
		for (size_t i = 0; i < Str.length(); ++i)
			if (Str[i] == ')')
			{
				size_t j;
				for (j = i; Str[j] != '('; --j)
					;
				Calculation.assign(Str, j, ++i - j);
				DoMultDiv(Calculation, SavedNumber);
				for (int k = 0; k < 100; ++k)
					if (Var[k] >= 'a' + SavedNumber)
						Var[k] = 0;
				Var[VarIndex] = 'a' + SavedNumber++;
				if (AddressIndex / 10 == 0)
					OutputFile << '0';
				OutputFile << AddressIndex++ << " STORE " << VarIndex << '\n';
				Str.erase(j, i - j);
				std::string VarToStr = "";
				VarToStr += Var[VarIndex--];
				Str.insert(j, VarToStr);
				i = 0;
			}
		Calculation.assign(Str, 4, Str.length());
		DoMultDiv(Calculation, SavedNumber);
		LetVal = FindVar(Str[0]);
		if (AddressIndex / 10 == 0)
			OutputFile << '0';
		OutputFile << AddressIndex++ << " STORE " << LetVal << '\n';
		for (int i = 0; i < 100; ++i)
			if (islower(Var[i]))
				Var[i] = 0;
	}
	else if (*command == "IF")
	{
		int OperBegin, Val1, Val2;;
		for(OperBegin = 0; Str[OperBegin] != '>' &&  Str[OperBegin] != '<' && Str[OperBegin] != '='; ++OperBegin)
			;
		IdentifyVal(&Val1, Str, OperBegin - 2);
		IdentifyVal(&Val2, Str, OperBegin + 2);
		if (Str[OperBegin] == '=')
		{
			if (AddressIndex/10 == 0)
				OutputFile << '0';
			OutputFile << AddressIndex++ << " LOAD " << Val1 << '\n';
			if (AddressIndex/10 == 0)
				OutputFile << '0';
			OutputFile << AddressIndex++ << " SUB " << Val2 << '\n';
			if (AddressIndex/10 == 0)
				OutputFile << '0';
			OutputFile << AddressIndex << " JZ " << AddressIndex + 2 << '\n';
			if (++AddressIndex/10 == 0)
				OutputFile << '0';
			OutputFile << AddressIndex++ << " JUMP \n";
		}
		else if (Str[OperBegin] == '<')
		{
			if (AddressIndex/10 == 0)
				OutputFile << '0';
			OutputFile << AddressIndex++ << " LOAD " << Val2 << '\n';
			if (AddressIndex/10 == 0)
				OutputFile << '0';
			OutputFile << AddressIndex++ << " SUB " << Val1 << '\n';
			if (AddressIndex/10 == 0)
				OutputFile << '0';
			OutputFile << AddressIndex++ << " JNEG \n";
		}
		else if (Str[OperBegin] == '>')
		{
			if (AddressIndex/10 == 0)
				OutputFile << '0';
			OutputFile << AddressIndex++ << " LOAD " << Val1 << '\n';
			if (AddressIndex/10 == 0)
				OutputFile << '0';
			OutputFile << AddressIndex++ << " SUB " << Val2 << '\n';
			if (AddressIndex/10 == 0)
				OutputFile << '0';
			OutputFile << AddressIndex++ << " SUB " << FindMemory("1") << '\n';
			if (AddressIndex/10 == 0)
				OutputFile << '0';
			OutputFile << AddressIndex++ << " JNEG \n";
		}
		++OperBegin;
		while (Str[++OperBegin] != ' ')
			;
		Str.erase(0, ++OperBegin);
		OperBegin = 0;
		while (Str[++OperBegin] != ' ')
			;
		(*command).assign(Str, 0, OperBegin);
		Str.erase(0, ++OperBegin);
		NeedNextString = true;
		if (*command == "GOTO")
			swap = true;
		TranslateCommand(command, Str);
	}
	else if (*command == "PRINT")
	{
		if (std::isdigit(Str[0]))
		{
			int ConstVal = FindMemory(Str);
			if (AddressIndex/10 == 0)
				OutputFile << '0';
			OutputFile << AddressIndex++ << " WRITE " << ConstVal << '\n';
		}
		else
		{
			int Var = FindVar(Str[0]);
			if (AddressIndex/10 == 0)
				OutputFile << '0';
			OutputFile << AddressIndex++ << " WRITE " << Var << '\n';
		}
	}
	else if (*command == "END")
	{
		if (AddressIndex/10 == 0)
			OutputFile << '0';
		OutputFile << AddressIndex++ << " HALT 00\n";
	}
	else if (*command == "GOTO")
	{
		GotoAddresses += Str + ' ';
		if (AddressIndex/10 == 0)
			OutputFile << '0';
		OutputFile << AddressIndex++ << " JUMP \n";
	}
}

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		std::cout << "Incorrect command\n";
		return -1;
	}
	int i;
 	std::string Str;
	std::string Field = "";
	AddressIndex = 0, VarIndex = 99;
	for (int i = 0; i < 100; ++i)
		Address[i] = 0;
	for (int i = 0; i < 100; ++i)
		Var[i] = 0;
	InputFile.open(*++argv, std::ios::in);
	OutputFile.open("Temple", std::ios::out);
	while(std::getline(InputFile, Str))
	{
		for (i = 0; Str[i] != ' ' && Str[i] != '\0'; ++i)
			;
		if (InputFile == '\0')
			break;
		Field.assign(Str, 0, i);
		++i;
		Str.erase(0, i);
		for (size_t j = 0; j < Field.length(); ++j)
			Address[AddressIndex] = Address[AddressIndex] * 10 + Field[j] - '0';
		if (NeedNextString)
		{
			if(swap)
			{
				Field += ' ';
				int k = GotoAddresses.length() - 2;
				while(isdigit(GotoAddresses[--k]))
					;
				GotoAddresses.insert(++k, Field);
				swap = false;
			}
			else
				GotoAddresses += Field + ' ';
		}
		NeedNextString = false;
		for (i =0 ; Str[i] != ' ' && Str[i] != '\0'; ++i)
			;
		Field.assign(Str, 0, i);
		Str.erase(0, ++i);
		TranslateCommand(&Field, Str);
  	}
	InputFile.close();
	OutputFile.close();
	InputFile.open("Temple", std::ios::in);
	OutputFile.open(*++argv, std::ios::out);
	std::string Seek;
	int SeekInt;
	while(std::getline(InputFile, Seek))
	{
		OutputFile << Seek;
		if (Seek.find("JUMP") != std::string::npos || Seek.find("JNEG") != std::string::npos)
		{
			Seek.assign(GotoAddresses, 0, GotoAddresses.find(' '));
			GotoAddresses.erase(0, GotoAddresses.find(' ') + 1);
			SeekInt = 0;
			for (size_t i = 0; i < Seek.length(); ++i)
				SeekInt = SeekInt * 10 + Seek[i] - '0';
			for (int i = 0; i < 100; ++i)
				if (Address[i] == SeekInt)
				{
					SeekInt = i;
					break;
				}
			if (SeekInt < 10)
				OutputFile << '0';
			OutputFile << SeekInt;
		}
		OutputFile << '\n';
	}
	remove("Temple");
}
