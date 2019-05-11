#include "Header.h"

int CU(void)
{
	int operand, command, value, InputValue;
	uint16_t tempAccum;
	sc_memoryGet(CurrentMemoryAddress, &value);
	if (sc_commandDecode(value, &command, &operand) == -1)
	{
		sc_regSet(FlagIncorrectCommand, 1);
		CheckFlags();
		return -1;
	}

	if (command >= 0x30 && command <= 0x34)
		return ALU(command, operand) == 0 ? 0 : -1;

	switch(command)
	{
		case 0x10:
			alarm(0);
			rk_mytermregime(1, 1, 1, 1, 1);
			std::cin >> InputValue;
			if (InputValue < 0 || InputValue > 127)
				return -1;
			Memory[CurrentMemoryAddress] >>= 7;
			Memory[CurrentMemoryAddress] <<= 7;
			Memory[CurrentMemoryAddress] |= InputValue;
			UpdateMemoryLocation(Green, White);
			PrintBigSymbols(CurrentMemoryAddress);
			rk_mytermregime(0, 0, 1, 0, 1);
			break;
		case 0x11:
			std::cout << operand;
			break;
		case 0x20:
			Accumulator = operand;
			PrintAccumulator();
			break;
		case 0x21:
			if (Accumulator < 0 || Accumulator > 127)
				return -1;
			Memory[CurrentMemoryAddress] >>= 7;
			Memory[CurrentMemoryAddress] <<= 7;
			Memory[CurrentMemoryAddress] |= Accumulator;
			break;
		case 0x40:
			ChangeMemAddress(operand);
			break;
		case 0x41:
			if (Accumulator < 0)
				ChangeMemAddress(operand);
			break;
		case 0x42:
			if (Accumulator == 0)
				ChangeMemAddress(operand);
			break;
		case 0x43:
			alarm(0);
			break;
		case 0x69:
			Accumulator %= 16;
			tempAccum = (uint16_t) operand << Accumulator;
			operand >>= 16 - Accumulator;
			Accumulator = operand | tempAccum;
			PrintAccumulator();
			break;
		default:
			return -1;
	}
	return 0;
}

int ALU(int command, int operand)
{
	int value;
	sc_memoryGet(CurrentMemoryAddress, &value);
	switch(command)
	{
		case 0x30:
			Accumulator += operand;
			if (Accumulator > 65535 || Accumulator < -65535)
			{
				sc_regSet(FlagAccumulatorOvervlow, 1);
				return -1;
			}
			break;
		case 0x31:
			Accumulator -= operand;
			if (Accumulator > 65535 || Accumulator < -65535)
			{
				sc_regSet(FlagAccumulatorOvervlow, 1);
				return -1;
			}
			break;
		case 0x33:
			Accumulator *= operand;
			if (Accumulator > 65535 || Accumulator < -65535)
			{
				sc_regSet(FlagAccumulatorOvervlow, 1);
				return -1;
			}
			break;
		case 0x32:
			if (operand == 0)
			{
				sc_regSet(FlagZeroDivision, 1);
				return -1;
			}
			Accumulator /= operand;
			break;
		default:
			return -1;
	}
	PrintAccumulator();
	return 0;
}
