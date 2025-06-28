#include "header.h"

void	help(void)
{
	printf("Usage: ping [OPTION...] HOST ...\n");	
	printf("Send ICMP ECHO_REQUEST packets to network hosts.\n");
	printf("\n");

	printf("Options valid for all request types:\n");
	printf("\n");

	printf("-n, --numeric		do not resolve host addresses\n");
	printf("-r, --ignore-routing	send directly to a host on an attached network\n");
	printf("-v, --verbose		verbose output\n");

	printf("\n");

	printf("Options valid for --echo requests:\n");
	printf("\n");

	printf("-f, --flood		flood ping (root only)\n");
	printf("-?, --help		give this help list\n");
}
