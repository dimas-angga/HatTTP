#include <iostream>

#include "hatttp.h"
#include "request.h"
#include "response.h"

HatTTP::Response sampleResponse()
{
    std::string body = "<h1> The quick brown fox jumps over the lazy dog</h1>\n";
    HatTTP::Response response = HatTTP::Response::create(HTTP_200_OK, (byte *) body.data(), body.length());
    response.header()[HEADER_CONTENT_TYPE] = CONTENT_HTML_UTF8;

    return response;
}

int main()
{
    std::string requestBytes = \
        "GET /index.html HTTP/1.0" CRLF \
        "Host: localhost" CRLF \
        "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:32.0) Gecko/20100101 Firefox/32.0" CRLF \
        CRLF;

    HatTTP::Request request = HatTTP::Request::parse((byte *) requestBytes.data(), requestBytes.length());

    std::cout << "-- Request --\n";
    std::cout << requestBytes;
    std::cout << "Method: " << request.getMethod() << "\n";
    std::cout << "Resource Path: " << request.getResourcePath() << "\n";
    std::cout << "HTTP Version: " << request.getHttpVersion() << "\n";

    std::cout << "\n-- Response--\n";
    HatTTP::Response response = sampleResponse();
    std::cout << response.compileHeader();
    std::cout << (const char *) response.getBody();

    return 0;
}
