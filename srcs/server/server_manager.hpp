#ifndef SERVER_MANAGER_HPP
#define SERVER_MANAGER_HPP

#include "client_session.hpp"
#include "configuration.hpp"
#include "define.hpp"
#include "http_request_parser.hpp"
#include "tcp_socket.hpp"
#include <map>
#include <vector>

namespace server {

class ServerManager {

private:
	const Configuration& configuration_;
	std::vector<server::TcpSocket> sockets_;
	std::map<int, ClientSession> client_session_;
	fd_set master_read_fds_;
	fd_set master_write_fds_;
	fd_set read_fds_;
	fd_set write_fds_;
	int highest_sd_;
	bool is_running;
	struct timeval timeout_;
	// std::map<int, SERVER_STATUS> server_status_;
	HttpRequestParser http_request_parser_;

	ServerManager();
	int setupServerSockets();
	int setupSelectReadFds();
	int monitorSocketEvents();
	int dispatchSocketEvents(int ready_sds);
	bool isListeningSocket(int sd);
	int acceptIncomingConnection(int listen_sd);
	// int createServerStatus(int sd);
	int receiveAndParseHttpRequest(ClientSession& client_session);
	void determineRequestType(int sd);
	int setWriteFd(int sd);
	int sendResponse(int sd);
	int requestCleanup(int sd);
	int disconnect(ClientSession& client_session);

	void registerClientSession(int sd, sockaddr_in client_address, sockaddr_in server_address);
	ClientSession& getClientSession(int const sd);

public:
	ServerManager(const Configuration& configuration);
	virtual ~ServerManager();
	explicit ServerManager(const ServerManager& other);
	ServerManager& operator=(const ServerManager& other);
	int runServer();
};

} // namespace server

#endif
