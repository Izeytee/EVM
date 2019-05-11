#include "Header.h"

char *KeyCode = new char[8];

int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint)
{
	struct termios term;
	if (tcgetattr(0, &term) == -1)
		return -1;
	regime ? term.c_lflag |= ICANON : term.c_lflag &= ~ICANON;
	sigint ? term.c_lflag |= ISIG : term.c_lflag &= ~ISIG;
	echo ? term.c_lflag |= ECHO : term.c_lflag &= ~ECHO;
	if (vtime < 0)
		return -1;
	term.c_cc[VTIME] = vtime;
	if (vmin < 0)
		return -1;
	term.c_cc[VMIN] = vmin;
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
	for (int i = 0; i < 8; ++i)
		KeyCode[i] = 0;
	if (tcgetattr(0, &term) == -1)
		return -1;
	if (rk_mytermregime(0, 0, 1, 0, 0) == -1)
		return -1;
	if (read(0, KeyCode, 8) <= 0)
		return -1;
	if (rk_mytermregime(1, 1, 1, 1, 1) == -1)
		return -1;
	std::string StringKeyCode = KeyCode;
	IdentifyKey(StringKeyCode, key);
	return 0;
}
