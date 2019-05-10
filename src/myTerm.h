#ifndef _MY_TERM_H
#define _MY_TERM_H

int mt_clrscr(void);
int mt_gotoXY(int X, int Y);
int mt_getscreensize(int *rows, int *cols);
int mt_setfgcolor(enum colors C);
int mt_setbgcolor(enum colors C);

#endif
