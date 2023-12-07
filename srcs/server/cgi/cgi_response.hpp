#ifndef CGI_RESPONSE_HPP
#define CGI_RESPONSE_HPP

#include <cctype>
#include <cstring>
#include <errno.h>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <sys/wait.h>
#include <webserv.hpp>

namespace cgi {

enum CGI_RESPONSE_STAGE { NOT_STARTED, HEADERS_SENT, BODY_SENT, COMPLETE };

class CgiResponse {

private:
	CGI_RESPONSE_STAGE stage_;
	int socket_vector_[2];
	pid_t pid_;
	int status_;
	std::string headers_stream_;
	std::map<std::string, std::string> headers_;
	std::string body_;
	std::size_t content_length_;

	void parseHeaders();

public:
	CgiResponse();
	CgiResponse(const CgiResponse& other);
	CgiResponse& operator=(const CgiResponse& other);
	~CgiResponse();

	void advanceResponseProcessing(std::string const& value);
	void setStage(CGI_RESPONSE_STAGE const stage);
	int readCgiReponse();
	void setSocketFd(int index, int fd);
	void setPid(pid_t pid);
	CGI_RESPONSE_STAGE getStage() const;
	int getSocketFd(int index) const;
	pid_t getPid() const;
	int getStatus() const;
	const std::map<std::string, std::string>& getHeaders() const;
	const std::string& getBody() const;
	std::string const getHeaderValue(std::string const& key) const;
	std::size_t getContentLength() const;
};

std::ostream& operator<<(std::ostream& out, const CgiResponse& cgi_response);

} // namespace cgi

#endif