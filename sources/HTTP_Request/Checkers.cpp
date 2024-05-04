/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Checkers.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 03:59:00 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/04 03:59:07 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/HTTP_Request.hpp"

bool HTTP_Request::checkCRLF(void) const
{
	if (this->content.find("\r\n\r\n") != std::string::npos)
		return (true);
	return (false);
}

bool HTTP_Request::checkContentLength(void) const
{
	if (this->request.post.headers.find("Content-Length") != this->request.post.headers.end())
		return (true);
	return (false);
}

bool HTTP_Request::checkChunked(void) const
{
	if (this->request.post.headers.find("Transfer-Encoding") != this->request.post.headers.end())
	{
		if (this->request.post.headers.find("Transfer-Encoding")->second == "chunked")
			return (true);
	}
	return (false);
}

bool HTTP_Request::checkMultipartDataForm(void) const
{
	if (this->request.post.headers.find("Content-Type") != this->request.post.headers.end())
	{
		if (this->request.post.headers.find("Content-Type")->second.find("multipart/form-data") != std::string::npos)
			return (true);
	}
	return (false);
}