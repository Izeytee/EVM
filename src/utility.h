#ifndef _UTILITY_H
#define _UTILITY_H

void Convert10to2(int Origin, std::string *Result);
void Convert2to10(std::string Origin, int *Result);
void InsertSymbolIn16(int Num, std::string *Result);
void Convert2to16(std::string Origin, std::string *Result);
void Convert16to2(std::string Origin, std::string *Result);
void Convert10to16(int Origin, std::string *Result);
void Convert16to10(std::string Origin, int *Result);
void PrintInterface();
void CheckFlags(void);
void PrintMem(void);
void InitBigSymbolDB(void);
void GetBigNumber(std::string origin, int *A);
void InitKeyDB(void);
void PrintBigSymbols(int address);
void ChangeMemValue(void);
void ChangeMemAddress(int Address);
void PrintInterface(void);
void PrintInstructionCounter(void);
void PrintAccumulator(void);
void PrintOperation(void);
void UpdateMemoryLocation(enum colors FC, enum colors BC);
int ReadAssemblerFile(int argc, char *argv[]);
int IdentifyKey(std::string KeyCommand, enum keys *key);
int SimpleCommand(enum keys key);
int IdentifyCells(char Symbol, int *Cells);
char identifyFlag(int value);
bool CheckCommand(int value);

#endif
