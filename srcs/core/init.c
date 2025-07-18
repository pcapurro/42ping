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

	infos->package.type = ECHO_REQUEST;
	infos->package.code = 0;

	infos->package.checksum = 0;
	infos->package.checksum = calculateChecksum(&infos->package);

	infos->package.id = getpid();
	infos->package.sequence = 1;
}
