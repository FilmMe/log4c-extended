#ifndef log4c_appender_type_udp_h
#define log4c_appender_type_udp_h

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef struct udp_udata
{
	int socketfd;
	char remoteip[20];
	unsigned int port;
	struct sockaddr_in serverSockAddr;
	int sockAddrSize;
} log4c_udp_udata_t;

extern const log4c_appender_type_t log4c_appender_type_udp;

#endif