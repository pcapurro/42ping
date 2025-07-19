#include "header.h"

void	writeStr(const char* str, const int value)
{
	for (int i = 0; str[i] != '\0'; i++)
		write(value, &str[i], 1);
}

uint16_t	calculateChecksum(tIcmp* ping, const int len)
{
	uint32_t	value = 0;

	ping->header.checksum = 0;

	for (int i = 0; i < (len / 2); i++)
		value += ((uint16_t *) ping)[i];

	while (value >> 16)
		value = (value & 0xFFFF) + (value >> 16);

	return ((uint16_t)(~value));
}

double	getTime(void)
{
	struct timespec	time = {0};
	double			value = 0;

	clock_gettime(CLOCK_MONOTONIC, &time);

	value = time.tv_sec * 1000.0 + (time.tv_nsec / 1e6);

	return (value);
}
