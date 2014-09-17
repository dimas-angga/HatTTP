#include "hatttp.h"
#include "request.h"
#include "response.h"
#include "server.h"

#define PORT 8787

int main(int argc, char **argv)
{
    struct ev_loop *loop = EV_DEFAULT;

    HatTTP::Server server(loop, PORT);
    server.start();

    return 0;
}
