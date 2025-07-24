#ifndef HEADER_H
# define HEADER_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <signal.h>
# include <errno.h>

# include <math.h>

# include <sys/types.h>
# include <sys/time.h>
# include <sys/socket.h>
# include <time.h>

# include <netinet/in.h>
# include <netinet/ip_icmp.h>
# include <arpa/inet.h>
# include <netdb.h>

# include "infos.h"

void		error(const int value, const char* str, const char c);

void		*registerHost(tInfos* infos, const char** argv);
void		*registerOptionsPOSIX(tInfos* infos, const char** argv);
void		*registerOptionsGNU(tInfos* infos, const char** argv);
void		*registerArguments(tInfos* infos, const char** argv);

void		writeStr(const char* str, const int value);
double		getTime(void);
uint16_t	calculateChecksum(tIcmp* ping, const int len);
void		*addTime(double** times, int* timesLen, const double newNumber);
void		registerTime(tInfos* infos);

bool		isErrorCode(const uint8_t type);
bool		isValidAnswer(tInfos* infos);
void		calculate(tInfos* infos);

void		printVerboseError(tInfos* infos, const unsigned char* answer, const int value);
void		printError(tInfos* infos, const unsigned char* answer, const int value);
void		printTitle(tInfos* infos);
void		printLog(tInfos* infos, const unsigned char* answer, const int value);
void		printFinal(tInfos* infos);

void		setToDefault(tInfos* infos);
void	    initializeHost(tInfos* infos);
void	    initializeSocket(tInfos* infos);
void	    initializePackage(tInfos* infos);
void	    initializeTime(tInfos* infos);
void		initialize(tInfos* infos);

void		freeData(tInfos* infos);
void		end(const int signal);
void		sendPing(tInfos* infos);
int			receivePong(tInfos* infos, unsigned char* answer);
void		ping(tInfos* infos);

void		help(void);
int			main(const int argc, const char** argv);

#endif
