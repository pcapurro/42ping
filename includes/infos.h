#ifndef INFOS_H
# define INFOS_H

# include <stdbool.h>

# include "icmp.h"

typedef struct sockaddr_in	tAddr;
typedef struct iphdr		ipHeader;

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
	socklen_t	destLen;
	tAddr		dest;

	tIcmp		ping;
	tIcmp		answer;

	const char*	host;
	const char*	ip;
};

typedef struct sInfos tInfos;

#endif