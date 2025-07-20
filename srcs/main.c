#include "header.h"

int		main(const int argc, const char** argv)
{
	tInfos	infos;

	if (registerArguments(&infos, argv + 1) == NULL)
		return (64);

	if (infos.help == true)
		help();
	else
		ping(&infos);

	(void) argc;

	return (0);
}
