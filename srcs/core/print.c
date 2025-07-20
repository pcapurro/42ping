#include "header.h"

void	printError(tInfos* infos, const unsigned char* answer, const int value)
{
	struct in_addr	source = {0};
	struct hostent*	host = NULL;

	char*			srcIp = NULL;
	char*			src = NULL;

	source.s_addr = infos->answerHdr->saddr;
	srcIp = inet_ntoa(source);

	host = gethostbyaddr(&source, sizeof(source), AF_INET);
	if (host == NULL || host->h_name == NULL)
		src = srcIp;
	else
		src = host->h_name;

	if (src == NULL || srcIp == NULL)
		src = "none", srcIp = "none";

	if (infos->errorType == ICMP_DEST_UNREACH)
	{
		printf("%d bytes from %s (%s): Destination not reachable\n", \
			value - (((struct iphdr*)answer)->ihl * 4), src, srcIp);
	}

	if (infos->errorType == ICMP_TIME_EXCEEDED)
	{
		printf("%d bytes from %s (%s): Time to live exceeded\n", \
			value - (((struct iphdr*)answer)->ihl * 4), src, srcIp);
	}

	if (infos->errorType == ICMP_PARAMETERPROB)
	{
		printf("%d bytes from %s (%s): Paramaters problem(s)\n", \
			value - (((struct iphdr*)answer)->ihl * 4), src, srcIp);
	}

	if (infos->verbose == true)
	{
		printf("IP Hdr Dump:\n");
		// printf("\0");

		printf("Vr	HL	TOS	Len	ID	Flg	off	TTL	Pro	cks	Src	Dst	Data\n");
		// printf("%d	%d	%x	%d	%d	%x	%x	%x	%x	%d	%d	%d	%d\n", 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42);

		printf("ICMP: type %d, code %d, size %d, id 0x%04x, seq 0x%04x\n", \
			infos->ping.header.type, infos->ping.header.code, 0, \
			infos->ping.header.un.echo.id, infos->ping.header.un.echo.sequence);
	}
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