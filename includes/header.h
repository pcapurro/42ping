#ifndef HEADER_H
# define HEADER_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include "infos.h"

void	writeStr(const char* str, const int value);

void	setToDefault(tInfos* infos);
void	getOptions(tInfos* infos, const char** argv);

void	error(const int value);

void	help(void);
int		main(const int argc, const char** argv);

#endif