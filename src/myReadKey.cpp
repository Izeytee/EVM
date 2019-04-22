#include "Header.h"

int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint)
{
	struct termios term;
	if (tcgetattr(0, &term) == -1)
		return -1;
	if (regime == 1)
		term.c_lflag |= ICANON;
	else
		if (regime == 0)
			term.c_lflag &= ~ICANON;
		else
			return -1;
	term.c_cc[VTIME] = vtime;
	term.c_cc[VMIN] = vmin;
	if (echo == 1)
		term.c_lflag |= ECHO;
	else
		if (echo == 0)
			term.c_lflag &= ~ECHO;
		else
			return -1;
	if (sigint == 1)
		term.c_lflag |= ISIG;
	else
		if (sigint == 0)
			term.c_lflag &= ~ISIG;
		else
			return -1;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return -1;
	return 0;
}

int rk_mytermsave()
{
	struct termios term;
	if (tcgetattr(0, &term) == -1)
		return -1;
	std::ofstream out("TermOptions", std::ios::out | std::ios::binary);
	if (!out)
		return -1;
	out.write((char*)&term, sizeof(term));
	out.close();
	return 0;
}

int rk_mytermrestore()
{
	struct termios term;
	std::ifstream in("TermOptions", std::ios::in | std::ios::binary);
	if (!in)
		return -1;
	in.read((char*)&term, sizeof(term));
	in.close();
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return -1;
	return 0;
}

int rk_readkey(enum keys *key)
{
	struct termios term;
	char *KeyCode = new char[8];
	if (tcgetattr(0, &term) == -1)
	{
		delete []KeyCode;
		return -1;
	}
	if (rk_mytermregime(0, 0, 1, 0, 0) == -1)
	{
		delete []KeyCode;
		return -2;
	}
	if (read(0, KeyCode, 8) <= 0)
	{
		delete []KeyCode;
		return -3;
	}
	if (rk_mytermregime(1, 1, 1, 1, 1) == -1)
	{
		delete []KeyCode;
		return -4;
	}
	std::string StringKeyCode = KeyCode;
	IdentifyKey(StringKeyCode, key);
	delete []KeyCode;
	return 0;
}
