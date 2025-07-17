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

void	setToDefault(tInfos* infos)
{
	infos->sent = 0;
	infos->received = 0;
	infos->loss = 0;

	infos->min = 0;
	infos->max = 0;
	infos->avg = 0;
	infos->stddev = 0;

	infos->socket = -1;
}

void	ping(tInfos* infos)
{
	struct hostent	*hostInfos = NULL;
	struct in_addr	addr;

	hostInfos = gethostbyname(infos->host);
	if (hostInfos == NULL)
		error(4, NULL, '\0');
	
	memset(&addr, 0, sizeof(addr));
	addr.s_addr = *(uint32_t *) hostInfos->h_addr_list[0];

	infos->ip = inet_ntoa(addr);
	// printf("%s\n", infos->ip);

	setToDefault(infos);
	infosPtr = infos;

	if (infos->verbose == false)
		printf("PING %s (%s) : 56 data bytes\n", infos->host, infos->ip);
	else
		printf("PING %s (%s) : 56 data bytes, id %p = %d\n", infos->host, infos->ip, NULL, 0);

	infos->socket = socket(AF_INET, SOCK_RAW, IPPROTO_COMP);
	if (infos->socket == -1)
		error(5, NULL, '\0');

	signal(SIGINT, end);
	while (42)
		;
}
