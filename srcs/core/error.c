#include "header.h"

void	error(const int value)
{
	if (value == 0)
		writeStr("ping: usage error: destination address required\n", 2);

	exit(1);
}
