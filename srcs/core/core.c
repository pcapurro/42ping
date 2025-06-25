#include "header.h"

void	setToDefault(tInfos* infos)
{
	infos->verbose = false;
	infos->quiet = false;
	infos->numeric = false;

	infos->timeout = 0;
	infos->size = 56;
	infos->interval = 1;

	infos->help = false;
}

void	getOptions(tInfos* infos, const char** argv)
{
	(void) infos;
	(void) argv;
}
