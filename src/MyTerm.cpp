#include "Header.h"

int mt_clrscr(void)
{
	std::cout << "\E[H[J";
	return 0;
}

int mt_gotoXY(int X, int Y)
{
	std::cout << "\E[" << X << ";" << Y << "H";
	return 0;
}

int mt_getscreensize(int *rows, int *cols)
{
	return 0;
}

int mt_setfgcolor(enum colors �)
{
	std::cout << "\E[3" << � <<"m";
	return 0;
}

int mt_setbgcolor(enum colors �)
{
	std::cout << "\E[4"<< � << "m";
	return 0;
}
