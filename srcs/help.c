#include "header.h"

void	help(void)
{
	printf("Usage: ping [option...] host\n");
	printf("\n");
	
	printf("Send ICMP ECHO_REQUEST packets to network hosts.\n");
	printf("\n");

	printf("-c, --count=N		stop after sending N packets\n");
	printf("-i, --interval=N	wait N seconds between sending each packet\n");
	printf("-i, --numeric		do not resolve host addresses\n");
	printf("-q, --quiet			quiet output\n");
	printf("-s, --size=N		send N data bytes in packets\n");
	printf("-v, --verbose		verbose output\n");
	printf("-w, --timeout=N		stop after N seconds\n");
	printf("-h, --help			display this help and exit\n");
}
