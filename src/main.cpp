#include <cstring>
#include <cstdio>

#include "hatttp.h"
#include "response.h"
#include "server.h"

int main(int argc, char **argv)
{
    // struct ev_loop *loop = EV_DEFAULT;

    //HatTTP::Server server;
    // TODO

    int sd;
    struct sockaddr_in addr;
    struct sockaddr_storage client_addr;
    socklen_t client_addr_size = sizeof(client_addr);
    socklen_t addr_size = sizeof(addr);

    sd = socket(PF_INET, SOCK_STREAM, 0);
    if (sd < 0) {
        perror("Socket Error");
        return -1;
    }

    memset(&addr, 0, addr_size);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8787);
    addr.sin_addr.s_addr = INADDR_ANY;

    int yes = 1;
    if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) != 0) {
        perror("SetSockOpt Error");
        return -1;
    }

    if (bind(sd, (struct sockaddr *) &addr, addr_size) != 0) {
        perror("Bind Error");
        return -1;
    }

    if (listen(sd, 5) < 0) {
        perror("Listen Error");
        return -1;
    }

    char buffer[4096];

    std::string body = "<h1>The quick brown fox jumps over the lazy dog<h1>\n";
    HatTTP::Response response = HatTTP::Response::create(HTTP_200_OK, (byte *) body.data(), body.length(), false);
    response.compileHeader();

    char reply1[] = "Hello, world!\r\n";
    char reply2[] = "Foo Bar\r\n";

    printf("Server listening http://0.0.0.0:%d/\n", 8787);

    while (true) {
        int cd = accept(sd, (struct sockaddr *) &client_addr, &client_addr_size);

        memset(buffer, 0, sizeof(buffer));
        recv(cd, buffer, 4096, 0);
        printf("%s", buffer);
        send(cd, response.getCompiledHeader().data(), response.getCompiledHeader().length(), 0);
        send(cd, response.getBody(), response.getLength(), 0);
        shutdown(cd, 2);
    }

    // ev_run(loop, 0);
    return 0;
}
