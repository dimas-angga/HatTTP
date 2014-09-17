#ifndef HATTTP_HATTTP_H_
#define HATTTP_HATTTP_H_

typedef unsigned char byte;

#define CRLF "\r\n"

#define HEADER_CONTENT_LENGTH "Content-Length"
#define HEADER_CONTENT_TYPE   "Content-Type"
#define HEADER_ACCEPT         "Accept"
#define HEADER_CONNECTION     "Connection"

#define HTTP1_0 "HTTP/1.0"
#define HTTP1_1 "HTTP/1.1"
#define CONTENT_HTML_UTF8 "text/html; charset=utf-8"
#define CONNECTION_CLOSE  "close"

namespace HatTTP
{

} /* HatTTP */

#endif /* HATTTP_HATTTP_H_ */
