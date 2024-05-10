/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 03:59:27 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/10 06:36:29 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/HTTP_Request.hpp"

void	HTTP_Request::parseRequestLine(void)
{
	std::string request_line;
	std::string _method;
    std::string _version;
    std::string _path;
	std::string _query;

	std::stringstream ss(this->content);
	std::getline(ss, request_line);
	std::stringstream ss2(request_line);

	ss2 >> _method >> _path >> _version;
	if (_path.find("?") != std::string::npos)
	{
		_query = _path.substr(_path.find("?") + 1);
		_path = _path.substr(0, _path.find("?"));
	}
	else
		_query = "";
	this->setMethod(_method);
	this->setParams(_path, _query, _version);
}

void	HTTP_Request::parseHeaders(void)
{
	std::string line;
	
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
		this->request.headers.insert(pair);
	}
}

void	HTTP_Request::parseBody(void)
{
	std::cout << "TODO" << std::endl;
}

void	HTTP_Request::parseRequest(void)
{
	this->parseRequestLine();
	this->parseHeaders();
	this->setBody();
	// this->parseBody();
}