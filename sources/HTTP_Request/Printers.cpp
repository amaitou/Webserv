/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Printers.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 04:00:07 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/05 03:40:04 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/HTTP_Request.hpp"

void HTTP_Request::printRequestLine(void) const
{
	this->printMethodType();
	std::cout << "Path: " << this->getPath() << std::endl;
	std::cout << "Query: " << this->getQuery() << std::endl;
	std::cout << "Version: " << this->getVersion() << std::endl;
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
	else if (this->request.method == DELETE)
	{
		std::map<std::string, std::string>::const_iterator it = this->request.delete_.headers.begin();
		while (it != this->request.delete_.headers.end())
		{
			std::cout << it->first << ": " << it->second << std::endl;
			it++;
		}
	}
	std::cout << std::endl;
}

void HTTP_Request::printBody(void) const
{
	std::cout << this->getBody() << std::endl;
	std::cout << std::endl;
}

void HTTP_Request::printMethodType(void) const
{
	if (this->getMethodType() == GET)
		std::cout << "Method: GET" << std::endl;
	else if (this->getMethodType() == POST)
		std::cout << "Method: POST" << std::endl;
	else if (this->getMethodType() == DELETE)
		std::cout << "Method: DELETE" << std::endl;
	else
		std::cout << "Method: NONE" << std::endl;
	std::cout << std::endl;
}

void HTTP_Request::printPostMethodType(void) const
{
	if (this->getPostContentType() == REGULAR_CHUNKED_BODY)
		std::cout << "Content-Type: Regular Chunked Body" << std::endl;
	else if (this->getPostContentType() == MULTIPART_FORM_DATA)
		std::cout << "Content-Type: Multipart Form Data" << std::endl;
	else if (this->getPostContentType() == MUTIPART_DATA_FORM_WITH_CHUNKED_BODY)
		std::cout << "Content-Type: Multipart Data Form With Chunked Body" << std::endl;
	else if (this->getPostContentType() == REGULAR_BODY)
		std::cout << "Content-Type: Regular Body" << std::endl;
	else
		std::cout << "Content-Type: NONE" << std::endl;
	std::cout << std::endl;
}