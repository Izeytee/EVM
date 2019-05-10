#include "Header.h"

void signalhandler(int signo)
{
	mt_gotoXY(1, 23);
	std::cout << "                                 ";
	mt_gotoXY(1, 23);
	if (CU() == -1)
	{	
		alarm(0);
		sc_regSet(FlagIgnoreClockPulse, 1);
		CheckFlags();
		return ;
	}
	UpdateMemoryLocation(Standart, Standart);
	CurrentMemoryAddress++;
	if (CurrentMemoryAddress > 99)
	{
		sc_regSet(FlagIgnoreClockPulse, 1);
		sc_regSet(MemoryOverFlow, 1);
		alarm(0);
		CheckFlags();
		return ;
	}
	UpdateMemoryLocation(Green, White);
	PrintOperation();
	PrintBigSymbols(CurrentMemoryAddress);
	alarm(1);
}

void sighandler(int signo)
{
	alarm(0);
	mt_clrscr();
	sc_regInit();
	sc_memoryInit();
	PrintInterface();
}

int Signal(void)
{	
	sc_regSet(FlagIgnoreClockPulse, 0);
	
	signal (SIGUSR1, sighandler);

	raise (SIGUSR1);

	return 0;
}

void Timer(void)
{
	sc_regSet(FlagIgnoreClockPulse, 1);
	
	struct itimerval nval, oval;

	signal (SIGALRM, signalhandler);

	nval.it_interval.tv_sec = 1;
 	nval.it_interval.tv_usec = 0;
 	nval.it_value.tv_sec = 1;
 	nval.it_value.tv_usec = 0;

	setitimer(ITIMER_REAL, &nval, &oval);
}
