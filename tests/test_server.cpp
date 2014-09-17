#include "hatttp.h"
#include "request.h"
#include "response.h"
#include "server.h"

#define PORT 8787

int main(int argc, char **argv)
{
    int server_sockfd;
    struct sockaddr_in server_addr;
    struct sockaddr_storage client_addr;
    socklen_t client_addr_size = sizeof(client_addr);
    socklen_t server_addr_size = sizeof(server_addr);

    server_sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (server_sockfd < 0) {
        perror("Socket Error");
        return -1;
    }

    memset(&server_addr, 0, server_addr_size);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    int yes = 1;
    if (setsockopt(server_sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) != 0) {
        perror("SetSockOpt Error");
        return -1;
    }

    if (bind(server_sockfd, (struct sockaddr *) &server_addr, server_addr_size) != 0) {
        perror("Bind Error");
        return -1;
    }

    if (listen(server_sockfd, 5) < 0) {
        perror("Listen Error");
        return -1;
    }

    char buffer[4096];
    std::string body = "<h1>The quick brown fox jumps over the lazy dog<h1>\n";
    HatTTP::Response response = HatTTP::Response::create(HTTP_200_OK, (byte *) body.data(), body.length(), false);
    response.compileHeader();

    printf("Server listening http://0.0.0.0:%d/\n", PORT);

    while (true) {
        int client_sockfd = accept(server_sockfd, (struct sockaddr *) &client_addr, &client_addr_size);

        memset(buffer, 0, sizeof(buffer));
        recv(client_sockfd, buffer, 4096, 0);
        printf("%s", buffer);

        send(client_sockfd, response.getCompiledHeader().data(), response.getCompiledHeader().length(), 0);
        send(client_sockfd, response.getBody(), response.getLength(), 0);

        shutdown(client_sockfd, 2);
    }

    return 0;
}
