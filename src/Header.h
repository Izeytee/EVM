#ifndef _HEADER_H
#define _HEADER_H

#define MemoryOverFlow 1
#define FlagIncorrectCommand 2
#define FlagZeroDivision 3
#define FlagIgnoreClockPulse 4
#define FlagAccumulatorOvervlow 5

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdio>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <signal.h>
#include <sys/time.h>
#include <stdint.h>

enum colors { Dark, Red, Green, Yellow, Blue, Black, Cyan, White, Standart = 9};
enum keys { Up, Right, Down, Left, Enter, Load, Save, Reset, Run, Step, F5, F6, Quit, WrongKey};
struct KeyCode{std::string KeyCommand; enum keys key;};
struct BigSymbol{char Symbol; int Cells[2];};

extern int Memory[100];
extern int sc_FlagRegister;
extern BigSymbol BSDB[19];
extern KeyCode KCDB[13];
extern int CurrentMemoryAddress;
extern int Accumulator;

#include "myBigChars.h"
#include "myTerm.h"
#include "myReadKey.h"
#include "utility.h"
#include "mySimpleComputer.h"
#include "mySignal.h"
#include "CPU.h"

#endif
