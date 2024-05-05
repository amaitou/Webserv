/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 03:59:27 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/05 06:13:59 by amait-ou         ###   ########.fr       */
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
		this->setParamsOfRequestLine(_path, _query, _version);
	}
	return (0);
}

void HTTP_Request::setParamsOfRequestLine(std::string &path, std::string &query, std::string &version)
{
	if (this->getMethodType() == GET)
	{
		this->request.get.path = path;
		this->request.get.query = query;
		if (path.find_last_of(".") != std::string::npos)
			this->request.get.extension = path.substr(path.find_last_of(".") + 1);
		else
			this->request.get.extension = "";
		this->request.get.version = version;
	}
	else if (this->getMethodType() == POST)
	{
		this->request.post.path = path;
		if (path.find_last_of(".") != std::string::npos)
			this->request.post.extension = path.substr(path.find_last_of(".") + 1);
		else
			this->request.post.extension = "";
		this->request.post.query = query;
		this->request.post.version = version;
		this->request.post.return_value = false;
	}
	else if (this->getMethodType() == DELETE)
	{
		this->request.delete_.path = path;
		if (path.find_last_of(".") != std::string::npos)
			this->request.delete_.extension = path.substr(path.find_last_of(".") + 1);
		else
			this->request.delete_.extension = "";
		this->request.delete_.query = query;
		this->request.delete_.version = version;
	}
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

int HTTP_Request::parseDeleteRequest(void)
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
		this->request.delete_.headers.insert(pair);
	}
	return (0);
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
		this->request.post.body = this->retrieveBodyFromChunkedData();
		return (0);
	}
	else
		return (1);
}

int HTTP_Request::parseWhenDataIsCompleted(std::string &content)
{
	this->parsePostHeaders();
	this->setPostContentType();
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

std::string HTTP_Request::retrieveBodyFromChunkedData(void)
{
	std::string body;
	std::string chunked_data = this->request.post.body;

	while (chunked_data.find("\r\n") != std::string::npos)
	{
		std::string chunk_size = chunked_data.substr(0, chunked_data.find("\r\n"));
		int size = std::stoi(chunk_size, 0, 16);
		if (size == 0)
			break;
		chunked_data = chunked_data.substr(chunked_data.find("\r\n") + 2);
		body += chunked_data.substr(0, size);
		chunked_data = chunked_data.substr(size + 2);
	}
	return (body);
}