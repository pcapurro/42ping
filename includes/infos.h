#ifndef INFOS_H
# define INFOS_H

# include "header.h"
# include "icmp.h"

struct sInfos
{
	bool		verbose;
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

	int			timesLen;
	double		*times;

	int			socket;

	bool		error;
	int			errorType;

	tAddr		src;
	tAddr		dest;

	tIcmp		ping;

	ipHdr*		answerHdr;
	tIcmp*		answer;

	const char*	host;
	const char*	ip;
};

typedef struct sInfos tInfos;

#endif
