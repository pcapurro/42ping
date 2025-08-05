#include "header.h"

void	error(const int value, const char* str, const char c)
{
	if (value == 1)
		writeStr("42ping: missing host operand\n", 2);

	if (value == 2)
	{
		writeStr("42ping: unrecognized option '", 2);
		writeStr(str, 2), writeStr("'\n", 2);
	}

	if (value == 3)
	{
		writeStr("42ping: invalid option -- '", 2);
		write(2, &c, 1), writeStr("'\n", 2);
	}

	if (value == 4)
		writeStr("42ping: unknown host\n", 2);

	if (value == 5)
	{
		if (str == NULL)
			str = "fatal error";

		writeStr("42ping: ", 2);
		writeStr(str, 2);
		writeStr("\n", 2);
	}

	if (value == 6)
		writeStr("42ping: fatal system error\n", 2);

	if (value == 4 || value == 5 || value == 6)
		exit(1);

	writeStr("Try '42ping --help' for more information.\n", 2);
}
