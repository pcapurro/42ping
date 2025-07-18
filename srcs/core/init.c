#include "header.h"

extern tInfos*	infosPtr;

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

void	initialize(tInfos* infos)
{
	struct hostent		*hostInfos = NULL;
	struct in_addr		addr;

	hostInfos = gethostbyname(infos->host);
	if (hostInfos == NULL)
		error(4, NULL, '\0');
	
	memset(&addr, 0, sizeof(addr));
	addr.s_addr = *(uint32_t *) hostInfos->h_addr_list[0];

	infos->ip = inet_ntoa(addr);
	// printf("%s\n", infos->ip);

	setToDefault(infos);
	infosPtr = infos;

	infos->socket = socket(AF_INET, SOCK_RAW, IPPROTO_COMP);
	if (infos->socket == -1)
		error(5, NULL, '\0');

	infos->ping.type = ECHO_REQUEST;
	infos->ping.code = 0;

	infos->ping.id = getpid();
	infos->ping.sequence = 0;

	for (int i = 0; i != 56; i++)
		infos->ping.data[i] = '\0';

	infos->ping.checksum = 0;

	// printf("%d\n", infos->ping.checksum);

	infos->dest.sin_family = AF_INET;
	if (inet_pton(AF_INET, infos->ip, &infos->dest.sin_addr) != 1)
		error(5, NULL, '\0');

	infos->destLen = sizeof(infos->dest);
}
