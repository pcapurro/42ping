#ifndef ICMP_H
# define ICMP_H

# include <stdint.h>

# define ECHO_REQUEST 8
# define ECHO_REPLY 0

struct sIcmp
{
	uint8_t		type;
	uint8_t		code;

	uint16_t	checksum;
	uint16_t	id;
	uint16_t	sequence;

};

typedef struct sIcmp tIcmp;

#endif