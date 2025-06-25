#include "header.h"

int	main(const int argc, const char** argv)
{
	if (argc == 1)
		error(0);

	tInfos	infos;

	setToDefault(&infos);

	getOptions(&infos, argv + 1);

	if (infos.help == true)
		help();

	return (0);
}
