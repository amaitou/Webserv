
#include "../../includes/HTTP_Request.hpp"

t_method_type	HTTP_Request::getMethodType(void) const
{
	return (this->request.method);
}

std::string	HTTP_Request::getContent(void) const
{
	return (this->content);
}

std::string	HTTP_Request::getPath(void) const
{
	return (this->request.path);
}

std::string HTTP_Request::getQuery(void) const
{
	return (this->request.query);
}

std::string HTTP_Request::getVersion(void) const
{
	return (this->request.version);
}

std::string HTTP_Request::getBody(void) const
{
	return (this->request.body);
}

std::map<std::string, std::string> HTTP_Request::getHeaders(void) const
{
	return (this->request.headers);
}

std::string HTTP_Request::getFileExtension(void) const
{
	return (this->request.extension);
}

std::string HTTP_Request::stringifyMethod(void) const
{
	if (this->request.method == GET)
		return ("GET");
	else if (this->request.method == POST)
		return ("POST");
	else if (this->request.method == DELETE)
		return ("DELETE");
	return ("NONE");
}