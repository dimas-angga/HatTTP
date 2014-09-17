#ifndef HATTTP_SERVER_H_
#define HATTTP_SERVER_H_

#include <ev.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>

namespace HatTTP
{

class Server
{
public:
    Server();
    ~Server();
private:

};

} /* HatTTP */

#endif /* HATTTP_SERVER_H_ */
