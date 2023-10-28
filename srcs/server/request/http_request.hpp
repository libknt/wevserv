#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP
#include <iostream>
#include <map>
#include <string>

namespace server {
namespace http_request_status {
enum HTTP_REQUEST_STATUS {
	METHOD,
	HEADER,
	BODY,
	FINISHED,
	ERROR,
	UNDEFINED,
};
}

namespace http_method {
enum HTTP_METHOD {
	GET,
	POST,
	DELETE,
	UNDEFINED,
};
}

namespace chunked_status {
enum CHUNKED_STATUS {
	CHUNKED_SIZE,
	CHUNKED_MESSAGE,
	UNDEFINED,
};
}

namespace http_version {
enum HTTP_VERSION {
	HTTP_1_0,
	HTTP_1_1,
	HTTP_2_0,
	UNDEFINED,
};
}

namespace http_error_status {
enum HTTP_ERROR_STATUS {
	BAD_REQUEST = 400,
	UNDEFINED,
};
}

namespace http_body_message_type {
enum HTTP_BODY_MESSAGE_TYPE {
	CONTENT_LENGTH,
	CHUNK_ENCODING,
	NONE,
	UNDEFINED,
};
}

class HttpRequest {
private:
	http_request_status::HTTP_REQUEST_STATUS status_;
	http_method::HTTP_METHOD method_;
	http_version::HTTP_VERSION version_;
	http_error_status::HTTP_ERROR_STATUS error_status_;
	http_body_message_type::HTTP_BODY_MESSAGE_TYPE body_message_type_;
	size_t content_length_;
	chunked_status::CHUNKED_STATUS chunked_status_;
	size_t chunked_size_;
	std::string request_path_;
	std::map<std::string, std::string> header_;
	std::string body_;
	int parseHttpMethod(std::string const& line);
	int parseHttpHeader(std::string const& line);
	int parseHttpBody(std::string const& line);
	int parseContentLengthBody(std::string const& line);
	int parseChunkedBody(std::string const& line);
	int checkHeaderValue();
	int setMethod(std::string const& method);
	int setRequestPath(std::string const& request_path);
	int setVersion(std::string const& version);
	int setHeaderValue(std::string const& key, std::string const& value);
	void setStatus(http_request_status::HTTP_REQUEST_STATUS const& status);
	void setErrorStatus(http_error_status::HTTP_ERROR_STATUS const& error_status);

public:
	explicit HttpRequest();
	HttpRequest(HttpRequest const& request);
	virtual ~HttpRequest();
	HttpRequest& operator=(HttpRequest const& request);
	int parseHttpRequest(std::string const& line);
	std::string getHeaderValue(std::string const& key);
	void getInfo(void);
	http_request_status::HTTP_REQUEST_STATUS getHttpRequestStatus(void);
	http_body_message_type::HTTP_BODY_MESSAGE_TYPE getHttpBodyMessageType(void);
};
}
#endif