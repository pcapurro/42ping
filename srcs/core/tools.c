#include "header.h"

void	writeStr(const char* str, const int value)
{
	for (int i = 0; str[i] != '\0'; i++)
		write(value, &str[i], 1);
}

uint16_t	calculateChecksum(tIcmp* ping)
{
	uint32_t	sum = 0;
	uint16_t	checksum = 0;
	uint16_t	value = 0;
	int			len = sizeof(tIcmp);

	ping->header.checksum = 0;

	for (int i = 0; i != len; i += 2)
	{
		value = ((uint8_t *)ping)[i] * 256;
		if (i + 1 < len)
			value += ((uint8_t *)ping)[i + 1];

		sum += value;

		if (sum > 0xFFFF)
			sum = (sum & 0xFFFF) + 1;
	}

	checksum = (uint16_t)sum;

	return (~checksum);
}
