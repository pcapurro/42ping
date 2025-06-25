#include "header.h"

void	help(void)
{
	printf("Usage: ping [OPTION...] HOST ...\n");	
	printf("Send ICMP ECHO_REQUEST packets to network hosts.\n");
	printf("\n");

	printf("Options:\n");
	printf("\n");

	printf("-v, --verbose		verbose output\n");
	printf("-?, --help		give this help list\n");
}
