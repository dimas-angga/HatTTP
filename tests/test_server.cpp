#include "hatttp.h"
#include "request.h"
#include "response.h"
#include "server.h"

#define PORT 8787

int main(int argc, char **argv)
{
    HatTTP::Server server(8787);
    server.start();

    return 0;
}
