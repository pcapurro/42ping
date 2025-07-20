#include "header.h"

tInfos*	infosPtr = NULL;

void	end(const int signal)
{
	(void) signal;

	if (infosPtr->socket != -1)
		close(infosPtr->socket);

	if (infosPtr->sent != 0)
		infosPtr->loss = 100.0 - (100.0 * ((double)infosPtr->received / (double)infosPtr->sent));

	int len = 0;
	for (int i = 0; infosPtr->times[i] != 0; i++)
		infosPtr->avg += infosPtr->times[i], len++;

	if (len != 0)
	{
		infosPtr->avg = infosPtr->avg / len;

		for (int i = 0; infosPtr->times[i] != 0; i++)
			infosPtr->stddev += (pow(infosPtr->times[i] - infosPtr->avg, 2));

		infosPtr->stddev = sqrt(infosPtr->stddev / len);
	}

	if (infosPtr->min == __DBL_MAX__)
		infosPtr->min = 0;

	if (infosPtr->times != NULL)
		free(infosPtr->times), infosPtr->times = NULL;

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
		printf("PING %s (%s) : 56 data bytes, id 0x%04x = %d\n", infos->host, infos->ip, infos->ping.header.un.echo.id, infos->ping.header.un.echo.id);

	if (infos->flood == true)
		printf("."), fflush(stdout);

	unsigned char	answer[1024] = {0};
	socklen_t		destLen = sizeof(infos->dest);
	int				value = 0;

	signal(SIGINT, end);
	while (42)
	{
		infos->ping.header.un.echo.sequence = htons(infos->sent);
		infos->ping.header.checksum = calculateChecksum(&infos->ping, sizeof(infos->ping));

		value = sendto(infos->socket, &infos->ping, 64, 0, \
			(struct sockaddr*)&infos->dest, destLen);

		if (value == -1)
			error(5, NULL, '\0');

		infos->start = getTime();
		infos->sent++;

		while (21)
		{
			value = recvfrom(infos->socket, answer, 4096, 0, \
				(struct sockaddr*)&infos->dest, &destLen);

			if (value == -1)
				error(5, NULL, '\0');

			infos->answer = (tIcmp*) (answer + ((struct iphdr*)answer)->ihl * 4);
			if (infos->answer->header.type == ICMP_ECHO \
				&& infos->answer->header.un.echo.id == infos->ping.header.un.echo.id \
				&& infos->answer->header.un.echo.sequence == infos->ping.header.un.echo.sequence)
				break ;
		}

		infos->end = getTime();
		infos->received++;

		if ((infos->end - infos->start) < infos->min)
			infos->min = infos->end - infos->start;

		if ((infos->end - infos->start) > infos->max)
			infos->max = infos->end - infos->start;

		addTime(&(infos->times), &(infos->timesLen), (infos->end - infos->start));

		if (infos->flood == false)
		{
			printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n", value - \
			(((struct iphdr*)answer)->ihl * 4), infos->ip, ntohs(infos->ping.header.un.echo.sequence), \
			((struct iphdr*)answer)->ttl, infos->end - infos->start);
			sleep(1);
		}
	}
}
