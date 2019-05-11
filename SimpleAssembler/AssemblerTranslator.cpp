#include <iostream>
#include <string>
#include <fstream>

int CheckCommand(std::string str)
{
	if (str == "READ")
		return 0x10;
	else if (str == "WRITE")
		return 0x11;
	else if (str == "LOAD")
		return 0x20;
	else if (str == "STORE")
		return 0x21;
	else if (str == "ADD")
		return 0x30;
	else if (str == "SUB")
		return 0x31;
	else if (str == "DIVIDE")
		return 0x32;
	else if (str == "MUL")
		return 0x33;
	else if (str == "JUMP")
		return 0x40;
	else if (str == "JNEG")
		return 0x41;
	else if (str == "JZ")
		return 0x42;
	else if (str == "HALT")
		return 0x43;
	else if (str == "RCCL")
		return 0x69;
	else if (str == "=")
		return 1;
	return -1;
}

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		std::cout << "Incorrect command\n";
		return -1;
	}
	std::ifstream InputFile(*++argv, std::ios::in);
	std::ofstream OutputFile(*++argv, std::ios::binary | std::ios::out);
 	std::string Str;
	int Commands[3];
	std::string Field = "";
	int i;
	while(InputFile)
	{
		std::getline(InputFile, Str);
		for (i = 0; Str[i] != ' ' && Str[i] != '\0'; ++i)
			;
		if (InputFile == '\0')
			break;
		Field.assign(Str, 0, i);
		++i;
		Str.erase(0, i);
		Commands[0] = (Field[0]- '0') * 10 + Field[1] - '0';
		if (Commands[0] < 0)
			return -1;
		OutputFile.write((char*)&Commands[0], sizeof(int));
		
		for (i = 0; Str[i] != ' '; ++i)
			;
		Field.assign(Str, 0, i);
		++i;
		Str.erase(0, i);
		Commands[1] = CheckCommand(Field);
		if (Commands[1] == -1)
			return -1;
		OutputFile.write((char*)&Commands[1], sizeof(int));

		for (i = 0; Str[i] != ' ' && Str[i] != '\0'; ++i)
			;
		Field.assign(Str, 0, i);
		Commands[2] = 0;
		for (size_t j = 0; j < Field.length(); j++)
		{
			if (Field[j] == '+')
				continue;
			Commands[2] *= 16;
			Commands[2] += (Field[j] - '0');
		}
		OutputFile.write((char*)&Commands[2], sizeof(int));
  	}
	InputFile.close();
	OutputFile.close();
}
