#ifndef INFOS_H
# define INFOS_H

# include "header.h"
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

	double		min;
	double		avg;
	double		max;
	double		stddev;

	double		start;
	double		end;

	int			socket;
	socklen_t	destLen;
	tAddr		dest;

	tIcmp		ping;
	tIcmp		answer;

	const char*	host;
	const char*	ip;
};

typedef struct sInfos tInfos;

#endif