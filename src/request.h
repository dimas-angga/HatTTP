#ifndef HATTTP_REQUEST_H_
#define HATTTP_REQUEST_H_

#include <string>

#include "hatttp.h"

namespace HatTTP
{

class Request
{
public:
    ~Request();

    static Request parse(const byte *requestBytes, size_t length);

    const std::string &getMethod();
    const std::string &getResourcePath();
    const std::string &getHttpVersion();

private:
    Request();

    std::string _method;
    std::string _resourcePath;
    std::string _httpVersion;
};

} /* HatTTP */

#endif /* HATTTP_REQUEST_H_ */
