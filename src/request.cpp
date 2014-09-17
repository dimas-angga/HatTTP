#include "request.h"

namespace HatTTP
{

Request::Request()
{

}

Request::~Request()
{

}

Request Request::parse(const byte *requestBytes, size_t length)
{
    Request request;

    // TODO: Real Parse
    request._method = "GET";
    request._resourcePath = "/index.html";
    request._httpVersion = "HTTP/1.0";

    return request;
}

const std::string &Request::getMethod()
{
    return _method;
}

const std::string &Request::getResourcePath()
{
    return _resourcePath;
}

const std::string &Request::getHttpVersion()
{
    return _httpVersion;
}

}
