/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTP_Request.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 05:34:21 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/04 04:01:32 by amait-ou         ###   ########.fr       */
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

/*
	Initialize the request with the file descriptor and the buffer
*/
void HTTP_Request::initRequest(int fd, char *buffer)
{
	this->setFd(fd);
	this->setNonBlocking();
	this->setContent(buffer);
	this->parseRequestLine();
}