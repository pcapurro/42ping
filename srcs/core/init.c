#include "header.h"

extern tInfos*	infosPtr;

void	setToDefault(tInfos* infos)
{
	infos->sent = 0;
	infos->received = 0;
	infos->loss = 0;

	infos->min = __DBL_MAX__;
	infos->max = 0;
	infos->avg = 0;
	infos->stddev = 0;

	infos->start = 0;
	infos->end = 0;

	infos->timesLen = 42;
	infos->times = NULL;

	infos->socket = -1;

	infos->answer = NULL;
}

void	initialize(tInfos* infos)
{
	struct hostent		*hostInfos = NULL;
	struct in_addr		addr = {0};

	hostInfos = gethostbyname(infos->host);
	if (hostInfos == NULL)
		error(4, NULL, '\0');
	
	memset(&addr, 0, sizeof(addr));
	addr.s_addr = *(uint32_t *) hostInfos->h_addr_list[0];

	infos->ip = inet_ntoa(addr);
	// printf("%s\n", infos->ip);

	setToDefault(infos);
	infosPtr = infos;

	infos->socket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (infos->socket == -1)
		error(5, NULL, '\0');

	infos->ping.header.type = ECHO_REQUEST;
	infos->ping.header.code = 0;

	infos->ping.header.un.echo.id = htons(getpid());
	infos->ping.header.un.echo.sequence = 0;

	for (int i = 0; i != 56; i++)
		infos->ping.data[i] = '\0';

	infos->ping.header.checksum = 0;

	infos->dest.sin_family = AF_INET;
	if (inet_pton(AF_INET, infos->ip, &infos->dest.sin_addr) != 1)
		error(5, NULL, '\0');

	infos->times = malloc(sizeof(double) * 42);
	if (!infos->times)
		close(infos->socket), error(6, NULL, '\0');

	infos->timesLen = 42;
	for (int i = 0; i != infos->timesLen; i++)
		infos->times[i] = 0;
}
