#include "header.h"

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

	printf("%s\n", infos->ip);
}
