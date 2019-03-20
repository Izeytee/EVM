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
	struct winsize ws;
	if (!ioctl(1, TIOCGWINSZ, &ws))
	{
		(*rows) = ws.ws_row;
		(*cols) = ws.ws_col; 
		return 0;
	}
	else
		return -1;
}

int mt_setfgcolor(enum colors Ñ)
{
	std::cout << "\E[3" << Ñ <<"m";
	return 0;
}

int mt_setbgcolor(enum colors Ñ)
{
	std::cout << "\E[4"<< Ñ << "m";
	return 0;
}
