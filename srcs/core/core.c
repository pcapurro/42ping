#include "header.h"

tInfos*	infosPtr = NULL;

void	end(const int signal)
{
	(void) signal;

	if (infosPtr->socket != -1)
		close(infosPtr->socket);

	if (infosPtr->sent != 0)
		infosPtr->loss = 100.0 - (100.0 * ((double)infosPtr->received / (double)infosPtr->sent));

	printf("\n");

	printf("--- %s ping statistics ---\n", infosPtr->host);
	printf("%d packets transmitted, %d packets received, %d%% packet loss\n", \
			infosPtr->sent, infosPtr->received, infosPtr->loss);
	printf("round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n", \
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

	unsigned char	answer[1024] = {0};
	int				value = 0;

	signal(SIGINT, end);
	while (42)
	{
		infos->ping.header.un.echo.sequence = htons(infos->sent);
		infos->ping.header.checksum = calculateChecksum(&infos->ping, sizeof(infos->ping));

		value = sendto(infos->socket, &infos->ping, 64, 0, \
			(struct sockaddr*)&infos->dest, infos->destLen);

		if (value == -1)
			error(5, NULL, '\0');

		infos->start = getTime();
		infos->sent++;

		while (21)
		{
			value = recvfrom(infos->socket, answer, 4096, 0, \
				(struct sockaddr*)&infos->dest, &infos->destLen);

			if (value == -1)
				error(5, NULL, '\0');

			infos->answer = (tIcmp*) (answer + ((struct iphdr*)answer)->ihl * 4);
			if (infos->answer->header.type == ECHO_REPLY \
				&& infos->answer->header.un.echo.id == infos->ping.header.un.echo.id \
				&& infos->answer->header.un.echo.sequence == infos->ping.header.un.echo.sequence)
				break ;
		}

		infos->end = getTime();
		infos->received++;

		printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n", value - \
			(((struct iphdr*)answer)->ihl * 4), infos->ip, infos->ping.header.un.echo.sequence / 256, \
			((struct iphdr*)answer)->ttl, infos->end - infos->start);

		if (infos->flood == false)
			sleep(1);
	}
}
