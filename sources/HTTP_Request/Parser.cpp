/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 03:59:27 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/04 06:00:52 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/HTTP_Request.hpp"

int	HTTP_Request::parseRequestLine(void)
{
	std::string request_line;
	std::string _method;
    std::string _version;
    std::string _path;
	std::string _query;
	
	if (this->checkCRLF() == false)
		return (1);
	else
	{
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
		this->setMethodType(request_line);
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
			this->request.post.return_value = false;
		}
	}
	return (0);
}

int HTTP_Request::parseGetRequest(void)
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

int HTTP_Request::parsePostRequest(void)
{
	std::string line;
	std::stringstream ss(content);

	if (this->request.post.return_value == false)
	{	
		if (!this->parseWhenDataIsCompleted(content))
			return (0);
	}
	else
		return (this->parseWhenDataIsNotCompleted(content));
	content.clear();
	return (1);
}

void HTTP_Request::parsePostHeaders(void)
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
		this->request.post.headers.insert(pair);
	}
}

int	HTTP_Request::parseRegularBody(std::string &content)
{
	int content_length = std::stoi(this->request.post.headers.find("Content-Length")->second);
	if ((int)this->request.post.body.length() < content_length)
	{
		this->request.post.body += content;
		return (1);
	}
	else
	{
		this->request.post.body += content.substr(0, content_length);
		return (0);
	}
}

int HTTP_Request::parseChunkedBody(std::string &content)
{
	this->request.post.body += content;
	if (this->request.post.body.find("\r\n0\r\n\r\n") != std::string::npos)
	{
		this->request.post.body += content;
		return (0);
	}
	else
		return (1);
}

int HTTP_Request::parseWhenDataIsCompleted(std::string &content)
{
	this->parsePostHeaders();
	this->setPostMethodType();
	if (this->checkContentLength())
	{
		std::string _content = content.substr(content.find("\r\n\r\n") + 4);
		this->parseRegularBody(_content);
	}
	else if (this->checkChunked())
	{
		std::string _content = content.substr(content.find("\r\n\r\n") + 4);
		if (!this->parseChunkedBody(_content))
			return (0);
	}
	this->request.post.return_value = true;
	return (1);
}

int HTTP_Request::parseWhenDataIsNotCompleted(std::string &content)
{
	if (this->checkContentLength())
		return (this->parseRegularBody(content));
	else if (this->checkChunked())
		return (this->parseChunkedBody(content));
	return (1);
}

/* TODO:
 * 1. retrieve data from the regular chunked data
 * 2. retrieve data from the multipart data form with chunked data
 * 3. Task retrieve data from multipart data form with regular data
 */

std::string HTTP_Request::retrieveRegularChunkedBody(void)
{
	return ("");
}