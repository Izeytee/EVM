#include "Header.h"

int bc_printA(char *str)
{
	std::cout << "\E(0" << str << "\E(B";
	return 0;
}

int bc_box(int x1, int x2, int y1, int y2)
{
	if (x1 >= x2 || y1 >= y2)
		return -1;
	mt_gotoXY(x1, y1);
	for (int i = 1; i <= x2 - x1; i++)
	{
		mt_gotoXY(x1 + i, y1);
		bc_printA((char*)"q");
		mt_gotoXY(x1 + i, y2);
		bc_printA((char*)"q");
	}
	for (int i = 1; i <= y2 - y1; i++)
	{
		mt_gotoXY(x1, y1 + i);
		bc_printA((char*)"x");
		mt_gotoXY(x2, y1 + i);
		bc_printA((char*)"x");
	}

	mt_gotoXY(x1, y1);
	bc_printA((char*)"l");
	mt_gotoXY(x1, y2);
	bc_printA((char*)"m");
	mt_gotoXY(x2, y1);
	bc_printA((char*)"k");
	mt_gotoXY(x2, y2);
	bc_printA((char*)"j");
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
			A[0] % 2 == 1 ? bc_printA((char*)"a") : bc_printA((char*)" ");
			A[0] >>= 1;
		}
		mt_gotoXY(x, y + i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			A[1] % 2 == 1 ? bc_printA((char*)"a") : bc_printA((char*)" ");
			A[1] >>= 1;
		}
		mt_gotoXY(x, y + i + 5);
	}
	mt_setfgcolor(Standart);
	mt_setbgcolor(Standart);
	return 0;
}

int bc_setbigcharpos(int *big, int x, int y, int value)
{
	if ((value != 0) && (value != 1 || x < 1 || x > 8 || y < 1 || y > 8))
		return -1;
	if (value == 1)
	{
		big[y / 5] |= (1 << ((y - 1) * 8 + x - 1));
		return 0;
	}
	if (value == 0)
	{
		big[y / 5] &= ~(1 << ((y - 1) * 8 + x - 1));
		return 0;
	}
	return -1;
}

int bc_getbigcharpos(int *big, int x, int y, int *value)
{
	if (x < 1 || x > 8 || y < 1 || y > 8)
		return -1;
	(*value) = (big[y / 5] >> ((y - 1) * 8 + x - 1)) & 0x1;
	return 0;
}

int bc_bigcharwrite(int fd, int *big, int count)
{
	write(fd, big, sizeof(count) * 2 * count);
	close(fd);
	return 0;
}

int bc_bigcharread(int fd, int * big, int need_count, int *count)
{
	(*count) = read(fd, big , sizeof(need_count) * 2 * need_count)/8;
	if ((*count) == 0)
		return -1;
	close(fd);
	return 0;
}
