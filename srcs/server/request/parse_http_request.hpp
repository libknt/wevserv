#ifndef PARSE_HTTP_REQUEST_HPP
#define PARSE_HTTP_REQUEST_HPP

#include "http_request.hpp"
#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <utility>
#include <vector>
#include "rules.hpp"

namespace server {

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif

class ParseHttpRequest {
private:
	std::map<int, HttpRequest> http_request_map_;
	std::map<int, std::string> http_line_stream_;
	int parseHttpRequest();
	int parseMethod();
	int parseHeader();
	int checkHeaderValue();
	int parseBody(std::string const& line);
	int parseContentLengthBody(std::string const& line);
	int parseChunkedBody(std::string const& line);

public:
	explicit ParseHttpRequest();
	explicit ParseHttpRequest(ParseHttpRequest& other);
	virtual ~ParseHttpRequest();
	ParseHttpRequest& operator=(ParseHttpRequest& other);
	int handleBuffer(int socketfd, char* buf);
	HttpRequest const& getRequest(int sd) const;
	void addAcceptClientInfo(int socketfd, sockaddr_in client_address, sockaddr_in server_address);
};

}
#endif
