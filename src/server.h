#ifndef HATTTP_SERVER_H_
#define HATTTP_SERVER_H_

#include <ev.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>

#include <exception>
#include <memory>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#define BACKLOG 10

#define CB_ARGS struct ev_loop *loop, struct ev_io *watcher, int revents

namespace HatTTP
{

class Server
{
public:
    Server(struct ev_loop *loop, short port);
    ~Server();

    static void acceptCallback(CB_ARGS);
    static void handleCallback(CB_ARGS);

    void start();

private:
    int _sockfd;
    struct sockaddr_in _addr;
    socklen_t _addr_size;
    short _port;
    bool _running;

    int _yes;

    struct ev_loop *_loop;
};

} /* HatTTP */

#endif /* HATTTP_SERVER_H_ */
