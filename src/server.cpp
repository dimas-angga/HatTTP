#include "response.h"
#include "server.h"

namespace HatTTP
{

Server::Server(short port)
    : _port(port), _yes(1), _addr_size(sizeof(_addr)), _running(false)
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

void Server::start()
{
    struct sockaddr_storage client_addr;
    socklen_t client_addr_size = sizeof(client_addr);

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

    char buffer[4096];
    std::string body = "<h1>The quick brown fox jumps over the lazy dog<h1>\n";
    HatTTP::Response response = HatTTP::Response::create(HTTP_200_OK, (byte *) body.data(), body.length(), false);
    response.compileHeader();


    while (_running) {
        int client_sockfd = accept(_sockfd, (struct sockaddr *) &client_addr, &client_addr_size);

        memset(buffer, 0, sizeof(buffer));
        recv(client_sockfd, buffer, 4096, 0);
        printf("%s", buffer);

        send(client_sockfd, response.getCompiledHeader().data(), response.getCompiledHeader().length(), 0);
        send(client_sockfd, response.getBody(), response.getLength(), 0);

        shutdown(client_sockfd, 2);
    }
}

} /* HatTTP */
