#include "header.h"

tInfos*	infosPtr = NULL;

void	end(const int signal)
{
	(void) signal;

	if (infosPtr->socket != -1)
		close(infosPtr->socket);

	calculate(infosPtr);

	if (infosPtr->times != NULL)
		free(infosPtr->times), infosPtr->times = NULL;

	printFinal(infosPtr);

	exit(0);
}

void	sendPing(tInfos* infos)
{
	int			value = 0;
	socklen_t	destLen = sizeof(infos->dest);

	infos->ping.header.un.echo.sequence = htons(infos->sent);
	infos->ping.header.checksum = calculateChecksum(&infos->ping, sizeof(infos->ping));

	value = sendto(infos->socket, &infos->ping, 64, 0, \
		(struct sockaddr*)&infos->dest, destLen);

	if (value == -1)
		error(5, NULL, '\0');

	infos->start = getTime();
	infos->sent++;
}

int	receivePong(tInfos* infos, unsigned char* answer)
{
	int			value = 0;
	socklen_t	destLen = sizeof(infos->dest);

	while (21)
	{
		value = recvfrom(infos->socket, answer, 4096, 0, \
			(struct sockaddr*)&infos->dest, &destLen);

		if (value == -1)
			error(5, NULL, '\0');

		infos->answerHdr = (ipHdr*) answer;
		infos->answer = (tIcmp*) (answer + ((struct iphdr*)answer)->ihl * 4);

		if (isValidAnswer(infos) == true)
			break ;
	}

	return (value);
}

void	ping(tInfos* infos)
{
	unsigned char	answer[1024] = {0};
	int				value = 0;

	initialize(infos);
	printTitle(infos);

	signal(SIGINT, end);

	while (42)
	{
		sendPing(infos);

		value = receivePong(infos, answer);

		if (infos->error == true)
			printError(infos, answer, value);
		else
		{
			registerTime(infos);
			printLog(infos, answer, value);
		}
	}
}
