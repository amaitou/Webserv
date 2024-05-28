
#include "../../includes/HTTP_Request.hpp"

void	HTTP_Request::printRequestLine(void) const
{
	std::cout << "______________________Request Line______________________\n" << std::endl;
	if (this->getMethodType() == GET)
		std::cout << "Method: GET" << std::endl;
	else if (this->getMethodType() == POST)
		std::cout << "Method: POST" << std::endl;
	else if (this->getMethodType() == DELETE)
		std::cout << "Method: DELETE" << std::endl;
	else
		std::cout << "Method: NONE" << std::endl;
	std::cout << "Path: " << this->getPath() << std::endl;
	std::cout << "Extension: " << this->getFileExtension() << std::endl;
	std::cout << "Query: " << this->getQuery() << std::endl;
	std::cout << "Version: " << this->getVersion() << std::endl;
	std::cout << std::endl;
}

void	HTTP_Request::printHeaders(void) const
{
	std::cout << "______________________Headers______________________\n" << std::endl;
	std::map<std::string, std::string>::const_iterator it = this->request.headers.begin();
	while (it != this->request.headers.end())
	{
		std::cout << it->first << ": " << it->second << std::endl;
		it++;
	}
	std::cout << std::endl;
}

void	HTTP_Request::printBody(void) const
{
	std::cout << "______________________Body______________________\n" << std::endl;
	std::cout << this->getBody() << std::endl;
}

void	HTTP_Request::printRequest(void) const
{
	this->printRequestLine();
	this->printHeaders();
	this->printBody();
}