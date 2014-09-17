#include <cstring>
#include <cstdio>

#include "hatttp.h"
#include "response.h"
#include "server.h"

int main(int argc, char **argv)
{
    struct ev_loop *loop = EV_DEFAULT;

    HatTTP::Server server;
    // TODO

    ev_run(loop, 0);
    return 0;
}
