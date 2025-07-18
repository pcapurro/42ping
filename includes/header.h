#ifndef HEADER_H
# define HEADER_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>

# include "infos.h"
# include "icmp.h"

void		writeStr(const char* str, const int value);
uint16_t	calculateChecksum(tIcmp* ping);

void		error(const int value, const char* str, const char c);

void		*registerHost(tInfos* infos, const char** argv);
void		*registerOptionsPOSIX(tInfos* infos, const char** argv);
void		*registerOptionsGNU(tInfos* infos, const char** argv);

void		*registerArguments(tInfos* infos, const char** argv);

void		setToDefault(tInfos* infos);

void		end(const int signal);
void		initialize(tInfos* infos);
void		ping(tInfos* infos);

void		help(void);
int			main(const int argc, const char** argv);

#endif