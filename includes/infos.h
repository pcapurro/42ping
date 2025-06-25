#ifndef INFOS_H
# define INFOS_H

# include <stdbool.h>

struct sInfos
{
	bool	verbose;
	bool	quiet;
	bool	numeric;

	int		timeout;
	int		size;
	int		interval;
	int		number;

	bool	help;
};

typedef struct sInfos tInfos;

#endif