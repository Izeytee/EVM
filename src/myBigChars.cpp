#include "Header.h"

int bc_printA(char *str)
{
	std::cout << "\E[11m" << str << "\E[10m";
}

int bc_box(int x1, int x2, int y1, int y2)
{
	if (x1 > x2 || y1 > y2)
		return -1;
	std::cout << "\E" << x1 << ";" << y1 << "H";
	for (int i = 0; i <= x2 - x1; i++)
	{
		std::cout << "\E" << x1 + i << ";" << y1 << "H\u2500";
		std::cout << "\E" << x1 + i << ";" << y2 << "H\u2500";
	}
	for (int i = 0; i <= y2 - y1; i++)
	{
		std::cout << "\E" << x1 << ";" << y1 + i << "H\u2502";
		std::cout << "\E" << x2 << ";" << y1 + i << "H\u2502";
	}
	std::cout << "\E" << x1 << ";" << y1 << "H\b\u250C";
	std::cout << "\E" << x2 << ";" << y1 << "H\b\u2510";
	std::cout << "\E" << x1 << ";" << y2 << "H\b\u2514";
	std::cout << "\E" << x2 << ";" << y2 << "H\b\u2518";
	return 0;
}

int bc_printbigchar(int A[2], int x, int y, enum colors CT, enum colors CB)
{
	mt_gotoXY(x, y);
	mt_setfgcolor(CT);
	mt_setbgcolor(CB);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			A[0] >> 1;
			if (A[0] & 1 == 1)
				std::cout << "\u2588";
			else
				std::cout << " ";
		}
		mt_gotoXY(x, y + i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			A[1] >> 1;
			if (A[1] & 1 == 1)
				std::cout << "\u2588";
			else
				std::cout << " ";
		}
		mt_gotoXY(x, y + i + 5);
	}
	return 0;
}

int bc_setbigcharpos(int *big, int x, int y, int value)
{
	if (value != 0 && value != 1 || x < 1 || x > 8 || y < 1 || y > 8)
		return -1;
	if (value == 1)
	{
		big[y / 5] = big[y / 5] | (1 << ((y - 1) * 8 + x - 1));
		return 0;
	}
	if (value == 0)
	{
		big[y / 5] = big[y / 5] & (~(1 << ((y - 1) * 8 + x - 1)));
		return 0;
	}
}

int bc_getbigcharpos(int *big, int x, int y, int *value)
{
	if (x < 1 || x > 8 || y < 1 || y > 8)
		return -1;
	(*value) = (big[y / 5] >> ((y - 1) * 8 + x - 1)) & 0x1;
	return 0;
}

int bc_bigcharwrite(int fd, int * big, int count)
{

}
