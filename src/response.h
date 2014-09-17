#ifndef HATTTP_RESPONSE_H_
#define HATTTP_RESPONSE_H_

#include <map>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>

#include "hatttp.h"

#define HTTP_200_OK 					"200 OK"
#define HTTP_302_FOUND 					"302 Found"
#define HTTP_400_BAD_REQUEST 			"400 Bad Request"
#define HTTP_401_UNAUTHORIZED 			"401 Unauthorized"
#define HTTP_403_FORBIDDEN 				"403 Forbidden"
#define HTTP_404_NOT_FOUND 				"404 Not Found"
#define HTTP_500_INTERNAL_SERVER_ERROR  "500 Internal Server Error"
#define HTTP_501_NOT_IMPLEMENTED 		"501 Not Implemented"

namespace HatTTP
{

/* HTTP Status Codes */

class Response
{
public:
    ~Response();

    static Response create(const char *status);
    static Response create(const char *status, byte *body, size_t length, bool copyBody = true);

    const std::string &getStatus();
    const byte *getBody();
    const size_t getLength();
    const std::string &getCompiledHeader();

    std::map<std::string, std::string> &header();

    const std::string &compileHeader();
    void setStatus(const char *status);
    void setContentType(const char *contentType);
    void setBody(byte *body, size_t length, bool copyBody = true);


private:
    Response();

    std::string _status;
    std::map<std::string, std::string> _header;
    std::string _headerCompiled;
    std::vector<byte> _bodyCopy;

    byte *_body = NULL;
    size_t _length = 0;
};

} /* HaTTP */

#endif /* HATTTP_RESPONSE_H_ */
