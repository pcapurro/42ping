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

	if (clock_gettime(CLOCK_MONOTONIC, &time) != 0)
		return (0);

	value = time.tv_sec * 1000.0 + (time.tv_nsec / 1e6);

	return (value);
}

void	calculate(tInfos* infos)
{
	if (infos->sent != 0)
		infos->loss = 100.0 - (100.0 * ((double)infos->received / (double)infos->sent));

	int len = 0;
	for (int i = 0; infos->times[i] != 0; i++)
		infos->avg += infos->times[i], len++;

	if (len != 0)
	{
		infos->avg = infos->avg / len;

		for (int i = 0; infos->times[i] != 0; i++)
			infos->stddev += (pow(infos->times[i] - infos->avg, 2));

		infos->stddev = sqrt(infos->stddev / len);
	}

	if (infos->min == __DBL_MAX__)
		infos->min = 0;
}

void	*addTime(double** times, int* timesLen, const double newNumber)
{
	int	len = 0;

	for (int i = 0; i != *timesLen && (*times)[i] != 0.0; i++)
		len++;

	if (len == *timesLen)
	{
		double*	newTimes = NULL;

		newTimes = malloc(sizeof(double) * (*timesLen + 42));
		if (!newTimes)
			return (NULL);

		int i = 0;
		while (i != *timesLen)
			newTimes[i] = (*times)[i], i++;
		newTimes[i] = newNumber;

		free(*times);
		*times = newTimes;

		*timesLen += 42;
	}
	else
		(*times)[len] = newNumber;

	return (times);
}

void	registerTime(tInfos* infos)
{
	infos->end = getTime();
	infos->received++;

	if ((infos->end - infos->start) < infos->min)
		infos->min = infos->end - infos->start;

	if ((infos->end - infos->start) > infos->max)
		infos->max = infos->end - infos->start;

	addTime(&(infos->times), &(infos->timesLen), (infos->end - infos->start));
}

bool	isValidAnswer(tInfos* infos)
{
	if (infos->answer->header.type == ICMP_ECHOREPLY)
	{
		infos->error = false;

		if (infos->answer->header.un.echo.id == infos->ping.header.un.echo.id \
			&& infos->answer->header.un.echo.sequence == infos->ping.header.un.echo.sequence)
			return (true);
	}
	
	if (isErrorCode(infos->answer->header.type) == true)
	{
		infos->error = true;
		infos->errorType = infos->answer->header.type;

		infos->answer = (tIcmp*)((char*)infos->answer + sizeof(struct icmphdr));
		infos->answerHdr = (ipHdr*) infos->answer;
		infos->answer = (tIcmp*)((char*)infos->answer + ((struct iphdr *)infos->answer)->ihl * 4);

		if (infos->answer->header.un.echo.id == infos->ping.header.un.echo.id \
			&& infos->answer->header.un.echo.sequence == infos->ping.header.un.echo.sequence)
			return (true);
	}

	return (false);
}

bool	isErrorCode(const uint8_t type)
{
	if (type == ICMP_DEST_UNREACH)
		return (true);

	if (type == ICMP_TIME_EXCEEDED)
		return (true);

	if (type == ICMP_PARAMETERPROB)
		return (true);

	return (false);
}
