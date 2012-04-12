static const char version[] = "$Id$";

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <log4c/appender.h>
#include "appender_type_udp.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

static int udp_open(log4c_appender_t* this)
{
    log4c_udp_udata_t * const udata = log4c_appender_get_udata(this);
    if(udata->socketfd) {
        return 0;
    }
    if(udata->remoteip && udata->port)
    {
        int sockFd;
        struct sockaddr_in serverSockAddr;
        int sockAddrSize = sizeof (struct sockaddr_in);
        if((sockFd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
        {
            fprintf (stderr, "Error creating socket\n");
            return -1;
        }
        bzero(&serverSockAddr, sockAddrSize);
        serverSockAddr.sin_family = AF_INET;
        serverSockAddr.sin_port = htons(udata->port);
        serverSockAddr.sin_addr.s_addr = inet_addr(udata->remoteip);
        
        udata->socketfd = sockFd;
        memcpy(&udata->serverSockAddr, &serverSockAddr, sizeof(struct sockaddr_in));
        udata->sockAddrSize = sockAddrSize;
        return 0;
    }
    return -1;
}

static int udp_append(log4c_appender_t* this, const log4c_logging_event_t* a_event)
{
    log4c_udp_udata_t * const udata = log4c_appender_get_udata(this);
    int ret = sendto(udata->socketfd, 
                     a_event->evt_rendered_msg, 
                     strlen(a_event->evt_rendered_msg), 
                     0, 
                     (struct sockaddr  *)&udata->serverSockAddr, 
                     udata->sockAddrSize);
    if(ret < 0) {
        fprintf(stderr, "sendto");
        close(udata->socketfd);
        udata->socketfd = 0;
        return -1;
    }
    return ret;
}

static int udp_close(log4c_appender_t* this)
{
    log4c_udp_udata_t * const udata = log4c_appender_get_udata(this);
    close(udata->socketfd);
    udata->socketfd = 0;
    return 0;
}

const log4c_appender_type_t log4c_appender_type_udp = {
    "udp",
    udp_open,
    udp_append,
    udp_close
};
