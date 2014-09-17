#ifndef HATTTP_SERVER_H_
#define HATTTP_SERVER_H_

#include <ev.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>

#include <exception>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#define BACKLOG 10

namespace HatTTP
{

class Server
{
public:
    Server(short port);
    ~Server();

    void start();

private:
    int _sockfd;
    struct sockaddr_in _addr;
    socklen_t _addr_size;
    short _port;
    bool _running;

    int _yes;
};

} /* HatTTP */

#endif /* HATTTP_SERVER_H_ */
