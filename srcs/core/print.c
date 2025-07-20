#include "header.h"

void	printError(tInfos* infos)
{
	(void) infos;
}

void	printTitle(tInfos* infos)
{
	if (infos->verbose == false)
		printf("PING %s (%s) : 56 data bytes\n", infos->host, infos->ip);
	else
		printf("PING %s (%s) : 56 data bytes, id 0x%04x = %d\n", infos->host, infos->ip, infos->ping.header.un.echo.id, infos->ping.header.un.echo.id);

	if (infos->flood == true)
		printf("."), fflush(stdout);
}

void	printLog(tInfos* infos, const unsigned char* answer, const int value)
{
	if (infos->flood == false)
	{
		printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n", value - \
		(((struct iphdr*)answer)->ihl * 4), infos->ip, ntohs(infos->ping.header.un.echo.sequence), \
		((struct iphdr*)answer)->ttl, infos->end - infos->start);

		sleep(1);
	}
}

void	printFinal(tInfos* infos)
{
	printf("\n");

	printf("--- %s ping statistics ---\n", infos->host);
	printf("%d packet(s) transmitted, %d packet(s) received, %d%% packet loss\n", \
			infos->sent, infos->received, infos->loss);
	printf("round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n", \
			infos->min, infos->avg, infos->max, infos->stddev);
}