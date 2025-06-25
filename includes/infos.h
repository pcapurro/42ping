#ifndef INFOS_H
# define INFOS_H

# include <stdbool.h>

struct sInfos
{
	bool		verbose;
	bool		help;

	const char*	ip;
};

typedef struct sInfos tInfos;

#endif