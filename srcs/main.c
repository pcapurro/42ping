#include "header.h"

void	error(const int value)
{
	if (value == 0)
		write(2, "ping: usage error: destination address required\n", 48);

	exit(1);
}

int	main(const int argc, const char** argv)
{
	if (argc == 1)
		error(0);

	(void) argv;

	return (0);
}
