#ifndef _MY_BIG_CHARS_H
#define _MY_BIG_CHARS_H

int bc_printA(char *str);
int bc_box(int x1, int x2, int y1, int y2);
int bc_printbigchar(int A[2], int x, int y, enum colors CT, enum colors CB);
int bc_setbigcharpos(int *big, int x, int y, int value);
int bc_getbigcharpos(int *big, int x, int y, int *value);
int bc_bigcharwrite(int fd, int * big, int count);
int bc_bigcharread(int fd, int * big, int need_count, int *count);

#endif
