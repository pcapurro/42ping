#ifndef INFOS_H
# define INFOS_H

# include <stdbool.h>

# include "icmp.h"

struct sInfos
{
	bool		verbose;
	bool		numeric;

	bool		routing;
	bool		flood;

	bool		help;

	int			received;
	int			sent;
	int			loss;

	float		min;
	float		avg;
	float		max;
	float		stddev;

	int			socket;
	tIcmp		package;

	const char*	host;
	const char*	ip;
};

typedef struct sInfos tInfos;

#endif