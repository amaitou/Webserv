/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTP_Request.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 05:34:21 by amait-ou          #+#    #+#             */
/*   Updated: 2024/04/26 19:25:18 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_method_type	HTTP_Request::getMethodType(void) const
{
	return (this->request.method);
}

std::string	HTTP_Request::getContent(void) const
{
	return (this->content);
}

void	HTTP_Request::setMethodType(t_method_type method)
{
	this->request.method = method;
}

void	HTTP_Request::setContent(char *content)
{
	this->content = std::string(content);
}

void	HTTP_Request::checkMethodType(void)
{
	std::string	request_line;

	std::stringstream ss(this->content);
	std::getline(ss, request_line);
	if (request_line.find("GET") != std::string::npos)
		this->request.method = GET;
	else if (request_line.find("POST") != std::string::npos)
		this->request.method = POST;
	else if (request_line.find("DELETE") != std::string::npos)
		this->request.method = DELETE;
	else
		this->request.method = NONE;
}

void	HTTP_Request::parseRequestLine(void)
{
	std::string request_line;
	std::string _method;
    std::string _version;
    std::string _path;
	std::string _query;
	
	std::stringstream ss(content);
	std::getline(ss, request_line);
	std::stringstream ss2(request_line);

	ss2 >> _method >> _path >> _version;
	if (_path.find("?") != std::string::npos)
	{
		_query = _path.substr(_path.find("?") + 1);
		_path = _path.substr(0, _path.find("?"));
	}
	else
		_query = "No Query";
	if (this->request.method == GET)
	{
		this->request.get.path = _path;
		this->request.get.query = _query;
		this->request.get.version = _version;
	}
	else if (this->request.method == POST)
	{
		this->request.post.path = _path;
		this->request.post.query = _query;
		this->request.post.version = _version;
	}
}

int	HTTP_Request::parseGetRequest(void)
{
	std::string line;
	
	std::stringstream ss(content);
	std::getline(ss, line);

	while (std::getline(ss, line) && line != "\r")
	{
		int position = line.find(":");
		std::string key = line.substr(0, position);
		std::string value = line.substr(position + 2);
		if (value.find("\r") != std::string::npos)
			value = value.substr(0, value.find("\r"));
		std::pair<std::string, std::string> pair(key, value);
		this->request.get.headers.insert(pair);
	}
	return (0);
}

void HTTP_Request::printRequestLine(void) const
{
	if (this->request.method == GET)
	{
		std::cout << "Method: GET" << std::endl;
		std::cout << "Path: " << this->request.get.path << std::endl;
		std::cout << "Query: " << this->request.get.query << std::endl;
		std::cout << "Version: " << this->request.get.version << std::endl;
	}
	else if (this->request.method == POST)
	{
		std::cout << "Method: POST" << std::endl;
		std::cout << "Path: " << this->request.post.path << std::endl;
		std::cout << "Query: " << this->request.post.query << std::endl;
		std::cout << "Version: " << this->request.post.version << std::endl;
	}
	std::cout << std::endl;
}

void HTTP_Request::printHeaders(void) const
{
	if (this->request.method == GET)
	{
		std::map<std::string, std::string>::const_iterator it = this->request.get.headers.begin();
		while (it != this->request.get.headers.end())
		{
			std::cout << it->first << ": " << it->second << std::endl;
			it++;
		}
	}
	else if (this->request.method == POST)
	{
		std::map<std::string, std::string>::const_iterator it = this->request.post.headers.begin();
		while (it != this->request.post.headers.end())
		{
			std::cout << it->first << ": " << it->second << std::endl;
			it++;
		}
	}
	std::cout << std::endl;
}

int	HTTP_Request::isContentLength(void) const
{
	if (this->request.post.headers.find("Content-Length") != this->request.post.headers.end())
		return (1);
	return (0);
}

int	HTTP_Request::isChunked(void) const
{
	if (this->request.post.headers.find("Transfer-Encoding") != this->request.post.headers.end())
	{
		if (this->request.post.headers.find("Transfer-Encoding")->second == "chunked")
			return (1);
	}
	return (0);
}

void	HTTP_Request::setPostType(void)
{
	if (this->isChunked())
		this->request.post.content_type = CHUNKED_TRANSFER_ENCODING;
	else if (this->isContentLength())
		this->request.post.content_type = CUSTOM_DATA;
	else
		this->request.post.content_type = _NONE;
}

void HTTP_Request::parseFullChunked(std::stringstream &ss)
{
	std::string line;

	while (std::getline(ss, line))
	{
		if (line.find("\r") != std::string::npos)
			line = line.substr(0, line.find("\r"));
		if (line == "0")
			break;
		std::getline(ss, line);
		if (line.find("\r") != std::string::npos)
			line = line.substr(0, line.find("\r"));
		this->request.post.body += line;
	}
}

void	HTTP_Request::parseNonFullChunked(char *buffer, int size)
{
	std::string line;
	while (!this->isDataEnded())
	{
		memset(buffer, 0, size);
		read(this->getFd(), buffer, size);
		this->setContent(buffer);
		std::stringstream ss(this->content);
		while (std::getline(ss, line))
		{
			if (line.find("\r") != std::string::npos)
				line = line.substr(0, line.find("\r"));
			if (line == "0")
				break;
			std::getline(ss, line);
			if (line.find("\r") != std::string::npos)
				line = line.substr(0, line.find("\r"));
			this->request.post.body += line;
		}
	}
}

void HTTP_Request::parseContentLength(std::stringstream &ss, char *buffer, int size)
{
	std::string line;
	while (std::getline(ss, line))
		this->request.post.body += line + "\n";
	while ((int)this->request.post.body.length()
		< std::stoi(this->request.post.headers.find("Content-Length")->second))
	{
		memset(buffer, 0, size);
		read(this->getFd(), buffer, size);
		this->setContent(buffer);
		std::stringstream ss(this->content);
		while (std::getline(ss, line))
			this->request.post.body += line + "\n";
	}
}

void HTTP_Request::parsePostRequest(char *buffer, int size)
{
	std::string line;
	std::string _content_type;
	
	std::stringstream ss(this->content);
	std::getline(ss, line);
	while (std::getline(ss, line) && line != "\r")
	{
		int position = line.find(":");
		std::string key = line.substr(0, position);
		std::string value = line.substr(position + 2);
		if (value.find("\r") != std::string::npos)
			value = value.substr(0, value.find("\r"));
		std::pair<std::string, std::string> pair(key, value);
		this->request.post.headers.insert(pair);
	}
	this->setPostType();
	if (this->request.post.content_type == CHUNKED_TRANSFER_ENCODING)
	{
		if (this->isDataEnded())
			this->parseFullChunked(ss);
		else
			this->parseNonFullChunked(buffer, size);
	}
	else if (this->request.post.content_type == CUSTOM_DATA)
		this->parseContentLength(ss, buffer, size);
	return;
}

int HTTP_Request::isDataEnded(void) const
{
	if (this->content.find("\r\n0\r\n") != std::string::npos)
		return (1);
	return (0);
}

void HTTP_Request::printTypeOfPostRequest(void) const
{
	if (this->request.post.content_type == CUSTOM_DATA)
		std::cout << "Content-Type: BODY" << std::endl;
	else if (this->request.post.content_type == CHUNKED_TRANSFER_ENCODING)
		std::cout << "Content-Type: CHUNKED" << std::endl;
	else
		std::cout << "Content-Type: _NONE" << std::endl;
	std::cout << std::endl;
}

void HTTP_Request::printBody(void) const
{
	if (this->request.method == POST)
		std::cout << this->request.post.body << std::endl;
	else
		std::cout << "No Body" << std::endl;
	std::cout << std::endl;
}

int HTTP_Request::getFd(void) const
{
	return (this->fd);
}

void HTTP_Request::setFd(int fd)
{
	this->fd = fd;
}

void HTTP_Request::initRequest(int fd, char *buffer)
{
	this->setFd(fd);
	this->setNonBlocking();
	this->setContent(buffer);
	this->checkMethodType();
	this->parseRequestLine();
}

void HTTP_Request::setNonBlocking(void)
{
	int flags = fcntl(this->getFd(), F_GETFL, 0);
	if (flags == -1)
		throw TCP_Exception::FailedToSetNonBlocking();
	if (fcntl(this->getFd(), F_SETFL, flags | O_NONBLOCK) == -1)
		throw TCP_Exception::FailedToSetNonBlocking();
}

void HTTP_Request::cleanMembers(void)
{
	this->content.clear();
	this->request.method = NONE;
	this->request.get.path.clear();
	this->request.get.query.clear();
	this->request.get.version.clear();
	this->request.get.headers.clear();
	this->request.post.path.clear();
	this->request.post.query.clear();
	this->request.post.version.clear();
	this->request.post.content_type = _NONE;
	this->request.post.headers.clear();
	this->request.post.body.clear();
}