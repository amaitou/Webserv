/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Printers.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 04:00:07 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/04 04:00:12 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/HTTP_Request.hpp"

void HTTP_Request::printRequestLine(void) const
{
	if (this->request.method == GET)
	{
		std::cout << "Method: GET" << std::endl;
		std::cout << "Path: " << this->request.get.path << std::endl;
		if (this->request.get.query != "")
			std::cout << "Query: " << this->request.get.query << std::endl;
		else
			std::cout << "Query: NONE" << std::endl;
		std::cout << "Version: " << this->request.get.version << std::endl;
	}
	else if (this->request.method == POST)
	{
		std::cout << "Method: POST" << std::endl;
		std::cout << "Path: " << this->request.post.path << std::endl;
		if (this->request.post.query != "")
			std::cout << "Query: " << this->request.post.query << std::endl;
		else
			std::cout << "Query: NONE" << std::endl;
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

void HTTP_Request::printBody(void) const
{
	if (this->request.method == POST)
		std::cout << this->request.post.body << std::endl;
	else
		std::cout << "No Body" << std::endl;
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
	if (this->request.post.content_type == REGULAR_CHUNKED_BODY)
		std::cout << "Content-Type: Regular Chunked Body" << std::endl;
	else if (this->request.post.content_type == MULTIPART_FORM_DATA)
		std::cout << "Content-Type: Multipart Form Data" << std::endl;
	else if (this->request.post.content_type == MUTIPART_DATA_FORM_WITH_CHUNKED_BODY)
		std::cout << "Content-Type: Multipart Data Form With Chunked Body" << std::endl;
	else if (this->request.post.content_type == REGULAR_BODY)
		std::cout << "Content-Type: Regular Body" << std::endl;
	else
		std::cout << "Content-Type: NONE" << std::endl;
	std::cout << std::endl;
}