#ifndef ICMP_H
# define ICMP_H

# include "header.h"

typedef struct icmphdr		tIcmpHdr;
typedef struct sockaddr_in	tAddr;

typedef struct sIcmp 		tIcmp;

struct sIcmp
{
	tIcmpHdr	header;
	char		data[56];

};

#endif