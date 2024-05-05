/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Setters.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 03:58:18 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/05 06:27:17 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/HTTP_Request.hpp"

void	HTTP_Request::setContent(char *content)
{
	this->content = std::string(content);
}

void HTTP_Request::setFd(int fd)
{
	this->fd = fd;
}

void HTTP_Request::setNonBlocking(void)
{
	int flags = fcntl(this->getFd(), F_GETFL, 0);
	if (flags == -1)
		throw TCP_Exception::FailedToSetNonBlocking();
	if (fcntl(this->getFd(), F_SETFL, flags | O_NONBLOCK) == -1)
		throw TCP_Exception::FailedToSetNonBlocking();
}

void	HTTP_Request::setMethodType(std::string &request_line)
{
	std::string method;
	std::stringstream rl(request_line);
	
	rl >> method;

	if (method == "GET")
		this->request.method = GET;
	else if (method == "POST")
		this->request.method = POST;
	else if (method == "DELETE")
		this->request.method = DELETE;
	else
		this->request.method = NONE;
}

void HTTP_Request::setPostContentType(void)
{
	if (this->checkChunked() && this->checkMultipartDataForm())
		this->request.post.content_type = MUTIPART_DATA_FORM_WITH_CHUNKED_BODY;
	else if (this->checkChunked())
		this->request.post.content_type = REGULAR_CHUNKED_BODY;
	else if (this->checkMultipartDataForm())
		this->request.post.content_type = MULTIPART_FORM_DATA;
	else if (this->checkContentLength())
		this->request.post.content_type = REGULAR_BODY;
	else
		this->request.post.content_type = _NONE;
}