#include "header.h"

tInfos*	infosPtr = NULL;

void	end(const int signal)
{
	(void) signal;

	if (infosPtr->socket != -1)
		close(infosPtr->socket);

	if (infosPtr->sent != 0)
		infosPtr->loss = 100.0 - (100.0 * ((float)infosPtr->received / (float)infosPtr->sent));

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

	int value = 0;

	signal(SIGINT, end);
	while (42)
	{
		infos->ping.header.un.echo.sequence++;
		infos->ping.header.checksum = calculateChecksum(&infos->ping);

		// printf("%d\n", infos->ping.header.checksum);

		value = sendto(infos->socket, &infos->ping, 64, 0, \
			(struct sockaddr*)&infos->dest, infos->destLen);

		if (value == -1)
			error(5, NULL, '\0');

		infos->sent++;

		value = recvfrom(infos->socket, &infos->answer, sizeof(infos->answer), 0, \
			(struct sockaddr*)&infos->dest, &infos->destLen);

		if (value == -1)
			error(5, NULL, '\0');

		infos->received++;

		printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%f ms\n", \
			value, infos->ip, infos->ping.header.un.echo.sequence, 0, 0.0);

		if (infos->flood == false)
			sleep(1);
	}
}
