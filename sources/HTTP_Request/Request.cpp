
#include "../../includes/HTTP_Request.hpp"

HTTP_Request::HTTP_Request(char *content)
{
	this->content = std::string(content);
	this->request.method = NONE;
}

HTTP_Request::HTTP_Request(void)
{
	this->content = "";
	this->request.method = NONE;
}

HTTP_Request::~HTTP_Request(void) {}

