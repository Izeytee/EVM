#ifndef _MYCOMUTER_SIMPLE_H
#define MYCOMUTER_SIMPLE_H

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define MemoryOverFlow 1
#define FlagIncorrectCommand 2
#define FlagIncorrectFlag 3

extern int Memory[100];
extern int sc_FlagRegister;
struct BigSymbol{char Symbol; int Cells[2];};
enum colors { Dark, Red, Green, Yellow, Blue, Black, Cyan, White, Standart = 9};
extern BigSymbol BSDB[18];

int sc_regInit(void);
int sc_regSet(int sc_register, int value);
int sc_regGet(int sc_register, int *value);
int sc_commandEncode(int command, int operand, int *value);
int sc_commandDecode(int value, int * command, int * operand);
int sc_memoryInit(void);
int sc_memorySet(int address, int value);
int sc_memoryGet(int address, int *value);
int sc_memorySave(char *filename);
int sc_memoryLoad(char *filename);

void Convert10to2(int Origin, std::string *Result);
void Convert2to10(std::string Origin, int *Result);
void InsertSymbolIn16(int Num, std::string *Result);
void Convert2to16(std::string Origin, std::string *Result);
void Convert16to2(std::string Origin, std::string *Result);
void Convert10to16(int Origin, std::string *Result);
void Convert16to10(std::string Origin, int *Result);
void PrintInterface();
bool CheckCommand(int value);
int IdentifyCells(char Symbol, int *Cells);
void CheckFlags(void);
char identifyFlag(int value);
void PrintMem(void);
void InitBigSymbolDB(void);
void GetBigNumber(std::string origin, int *A);

int mt_clrscr(void);
int mt_gotoXY(int X, int Y);
int mt_getscreensize(int *rows, int *cols);
int mt_setfgcolor(enum colors C);
int mt_setbgcolor(enum colors C);

int bc_printA(char *str);
int bc_box(int x1, int x2, int y1, int y2);
int bc_printbigchar(int A[2], int x, int y, enum colors CT, enum colors CB);
int bc_setbigcharpos(int *big, int x, int y, int value);
int bc_getbigcharpos(int *big, int x, int y, int *value);
int bc_bigcharwrite(int fd, int * big, int count);
int bc_bigcharread(int fd, int * big, int need_count, int *count);

#endif // !_MYCOMUTER_SIMPLE_H
