#ifndef HEADER_H
# define HEADER_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include "infos.h"

void	writeStr(const char* str, const int value);

void	error(const int value, const char* str, const char c);

void	*registerHost(tInfos* infos, const char** argv);
void	*registerOptionsPOSIX(tInfos* infos, const char** argv);
void	*registerOptionsGNU(tInfos* infos, const char** argv);

void	*registerArguments(tInfos* infos, const char** argv);

void	ping(tInfos* infos);

void	help(void);
int		main(const int argc, const char** argv);

#endif