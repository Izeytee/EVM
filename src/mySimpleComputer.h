#ifndef _MYCOMUTER_SIMPLE_H
#define _MYCOMUTER_SIMPLE_H

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

#endif
