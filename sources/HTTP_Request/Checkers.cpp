
#include "../../includes/HTTP_Request.hpp"

bool HTTP_Request::checkCRLF(void) const
{
	return (this->content.find("\r\n\r\n") != std::string::npos);
}

bool HTTP_Request::checkGetRequest(void) const
{
	return (this->checkCRLF() && this->content.find("GET") != std::string::npos);
}

bool HTTP_Request::checkDeleteRequest(void) const
{
	return (this->checkCRLF() && this->content.find("DELETE") != std::string::npos);
}

bool HTTP_Request::checkZeroCRLF(void) const
{
	return (this->content.find("\r\n0\r\n") != std::string::npos);
}

bool HTTP_Request::checkContentLength(void) const
{
	if (this->content.find("Content-Length: ") == std::string::npos)
		return (false);
	int start = this->content.find("Content-Length: ") + 16;
	int end = this->content.find("\r\n", start);
	std::string content_length = this->content.substr(start, end - start);
	size_t length = std::stoi(content_length);
	int body_start = this->content.find("\r\n\r\n") + 4;
	if (this->content.length() - body_start < length)
		return (false);
	return (true);
}

bool HTTP_Request::checkChunked(void) const
{
	return (this->content.find("Transfer-Encoding: chunked") != std::string::npos
		&& this->checkZeroCRLF());
}

bool HTTP_Request::checkPostRequest(void) const
{
	return (this->content.find("POST") != std::string::npos
		&& (this->checkChunked() || this->checkContentLength()));
}