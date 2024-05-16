/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 03:59:27 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/10 15:50:00 by amait-ou         ###   ########.fr       */
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
	if (this->checkChunked())
	{
		std::string body = "";
		size_t pos = 0;
		while (pos < this->request.body.size()) {
			size_t chunkSizeEnd = this->request.body.find("\r\n", pos);
			u_long hexa_chunked_size = std::stoul(this->request.body.substr(pos, chunkSizeEnd - pos), nullptr, 16);
			
			if (hexa_chunked_size == 0)
				break;
			pos = chunkSizeEnd + 2; 
			
			std::string chunk = this->request.body.substr(pos, hexa_chunked_size);
			body += chunk;
			
			pos += hexa_chunked_size + 2;

			if (this->request.body.substr(pos, 2) == "\r\n")
			pos += 2;
		}
		
		this->request.body = body;
	}
}

void	HTTP_Request::parseRequest(void)
{
	this->parseRequestLine();
	this->parseHeaders();
	this->setBody();
	this->parseBody();
}