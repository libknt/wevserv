#ifndef CGI_REQUEST_HPP
#define CGI_REQUEST_HPP
#include "webserv.hpp"
#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <map>
#include <signal.h>
#include <sstream>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

namespace cgi {
enum CGI_STATUS {
	UNDIFINED,
	EXECUTED,
};

class CgiRequest {
private:
	CGI_STATUS cgi_status_;
	std::map<std::string, std::string> meta_variables_;
	pid_t pid_;
	int socket_vector_[2];
	char** execve_argv_;
	char** environ_;
	int status_;

	int setNonBlocking(int sd);
	int setupInterProcessCommunication();
	char** mapToCharStarStar(std::map<std::string, std::string> const& map);
	int shebang(std::string file, std::string& path);
	char** createExecveArgv();

public:
	CgiRequest(const std::map<std::string, std::string> meta_variables);
	CgiRequest(const CgiRequest& other);
	CgiRequest& operator=(const CgiRequest& other);
	~CgiRequest();
	int setup();
	int execute();
	int getSocketFd(int const index) const;
	std::string findMetaVariable(std::string const& key) const;
	CGI_STATUS getStatus() const;
	pid_t getPid() const;
};

std::ostream& operator<<(std::ostream& out, const CgiRequest& cgi);

} // namespace

#endif // CGI_HPP