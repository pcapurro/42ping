#include "header.h"

tInfos*	infosPtr = NULL;

void	end(const int signal)
{
	(void) signal;

	if (infosPtr->socket != -1)
		close(infosPtr->socket);
	
	printf("\n");

	printf("--- %s ping statistics ---\n", infosPtr->host);
	printf("%d packets transmitted, %d packets received, %d%% packet loss\n", \
			infosPtr->sent, infosPtr->received, infosPtr->loss);
	printf("round-trip min/avg/max/stddev = %f/%f/%f/%f ms\n", \
			infosPtr->min, infosPtr->avg, infosPtr->max, infosPtr->stddev);

	exit(0);
}

void	ping(tInfos* infos)
{
	initialize(infos);

	if (infos->verbose == false)
		printf("PING %s (%s) : 56 data bytes\n", infos->host, infos->ip);
	else
		printf("PING %s (%s) : 56 data bytes, id %p = %d\n", infos->host, infos->ip, NULL, 0);

	signal(SIGINT, end);
	while (42)
		;
}
