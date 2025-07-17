#include "header.h"

void	error(const int value, const char* str, const char c)
{
	if (value == 1)
		writeStr("ping: missing host operand\n", 2);

	if (value == 2)
	{
		writeStr("ping: unrecognized option '", 2);
		writeStr(str, 2), writeStr("'\n", 2);
	}

	if (value == 3)
	{
		writeStr("ping: invalid option -- '", 2);
		write(2, &c, 1), writeStr("'\n", 2);
	}

	if (value == 4)
	{
		writeStr("ping: unknown host\n", 2);
		exit(1);
	}

	if (value == 5)
	{
		perror("");
		writeStr("ping: fatal network error\n", 2);
		exit(1);
	}

	writeStr("Try 'ping --help' for more information.\n", 2);
}
