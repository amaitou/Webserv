/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTP_Request.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 05:34:21 by amait-ou          #+#    #+#             */
/*   Updated: 2024/03/08 06:53:37 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HTTP_Request.hpp"

HTTP_Request::HTTP_Request(char *content)
{
	this->content = std::string(content);
	this->request.method = NONE;
	memset(&this->request.get, 0, sizeof(this->request.get));
	memset(&this->request.post, 0, sizeof(this->request.post));
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
	
	std::stringstream ss(content);
	std::getline(ss, request_line);
	std::stringstream ss2(request_line);

	ss2 >> _method >> _path >> _version;
}

int	HTTP_Request::parseGetRequest(void)
{
	std::string line;
	
	std::stringstream ss(content);
	std::getline(ss, line);
	while (std::getline(ss, line))
	{
		if (line.empty())
			break;
	}
}