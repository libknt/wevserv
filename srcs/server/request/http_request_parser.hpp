#ifndef PARSE_HTTP_REQUEST_HPP
#define PARSE_HTTP_REQUEST_HPP

#include "webserv.hpp"
#include "http_request.hpp"
#include "server_directive.hpp"
#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <utility>
#include <vector>

namespace server {

namespace parse_request_line {
enum PARSE_REQUEST_LINE {
	METHOD,
	URI,
	VERSION,
};
}

namespace parse_header {
enum PARSE_HEADER {
	KEY,
	VALUE,
};
}

class HttpRequestParser {
private:
	HttpRequestParser();
	explicit HttpRequestParser(HttpRequestParser& other);
	virtual ~HttpRequestParser();
	HttpRequestParser& operator=(HttpRequestParser& other);

	static int parseRequest(HttpRequest& request, std::string const& line);
	static int parseStartLine(HttpRequest& request, std::string const& line);
	static int parseHeader(HttpRequest& request, std::string const& line);
	static int parseBody(HttpRequest& request, std::string const& line);
	static int parseContentLengthBody(HttpRequest& request, std::string const& line);
	static int parseChunkedBody(HttpRequest& request, std::string const& line);
	static int checkHeaderValue(HttpRequest& request);

public:
	static void parse(HttpRequest& request, const char* buf, const ServerDirective &server_directive);
};

}
#endif
