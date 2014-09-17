#include "response.h"
#include "server.h"

namespace HatTTP
{

Server::Server(struct ev_loop *loop, short port)
    : _loop(loop), _port(port), _yes(1), _addr_size(sizeof(_addr)),
      _running(false)
{
    _sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (_sockfd < 0) {
        perror("socket Error");
        throw "socket Error";
    }

    memset(&_addr, 0, _addr_size);
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(_port);
    _addr.sin_addr.s_addr = INADDR_ANY;

    if (setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &_yes, sizeof(int)) != 0) {
        perror("setsockopt Error");
        throw "setsockopt Error";
    }
}

Server::~Server()
{

}

void Server::acceptCallback(CB_ARGS)
{
    struct sockaddr_storage client_addr;
    socklen_t client_addr_size = sizeof(client_addr);
    int client_sockfd;

    struct ev_io *w_client = (struct ev_io *) malloc(sizeof(struct ev_io));

    client_sockfd = accept(watcher->fd, (struct sockaddr *) &client_addr, &client_addr_size);

    ev_io_init(w_client, handleCallback, client_sockfd, EV_READ);
    ev_io_start(loop, w_client);
}

void Server::handleCallback(CB_ARGS)
{
    char buffer[4096];

    memset(buffer, 0, sizeof(buffer));
    recv(watcher->fd, buffer, 4096, 0);
    printf("%s", buffer);

    std::string body = "<h1>The quick brown fox jumps over the lazy dog<h1>\n";
    HatTTP::Response response = HatTTP::Response::create(HTTP_200_OK, (byte *) body.data(), body.length(), false);
    response.compileHeader();

    send(watcher->fd, response.getCompiledHeader().data(), response.getCompiledHeader().length(), 0);
    send(watcher->fd, response.getBody(), response.getLength(), 0);

    ev_io_stop(loop, watcher);
    shutdown(watcher->fd, 2);
    free(watcher);
}

void Server::start()
{
    struct ev_io w_accept;

    if (bind(_sockfd, (struct sockaddr *) &_addr, _addr_size) != 0) {
        perror("bind Error");
        throw "bind Error";
    }

    if (listen(_sockfd, BACKLOG) < 0) {
        perror("listen Error");
        throw "listen Error";
    }

    _running = true;

    printf("Server listening http://0.0.0.0:%d/\n", _port);

    ev_io_init(&w_accept, acceptCallback, _sockfd, EV_READ);
    ev_io_start(_loop, &w_accept);

    while (_running) {
        ev_loop(_loop, 0);
    }
}

} /* HatTTP */
