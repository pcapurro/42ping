#ifndef INFOS_H
# define INFOS_H

# include <stdbool.h>

struct sInfos
{
	bool		verbose;
	bool		help;

	int			received;
	int			sent;
	int			loss;

	float		min;
	float		avg;
	float		max;
	float		stddev;

	int			socket;

	const char*	host;
	const char*	ip;
};

typedef struct sInfos tInfos;

#endif