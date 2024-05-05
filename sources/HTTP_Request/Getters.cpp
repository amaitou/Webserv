/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Getters.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 03:57:24 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/05 03:24:35 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/HTTP_Request.hpp"

t_method_type	HTTP_Request::getMethodType(void) const
{
	return (this->request.method);
}

std::string	HTTP_Request::getContent(void) const
{
	return (this->content);
}

int HTTP_Request::getFd(void) const
{
	return (this->fd);
}

std::string	HTTP_Request::getPath(void) const
{
	if (this->request.method == GET)
		return (this->request.get.path);
	else if (this->request.method == POST)
		return (this->request.post.path);
	else if (this->request.method == DELETE)
		return (this->request.delete_.path);
	return ("");
}

std::string HTTP_Request::getQuery(void) const
{
	if (this->request.method == GET)
		return (this->request.get.query);
	else if (this->request.method == POST)
		return (this->request.post.query);
	else if (this->request.method == DELETE)
		return (this->request.delete_.query);
	return ("");
}

std::string HTTP_Request::getVersion(void) const
{
	if (this->request.method == GET)
		return (this->request.get.version);
	else if (this->request.method == POST)
		return (this->request.post.version);
	else if (this->request.method == DELETE)
		return (this->request.delete_.version);
	return ("");
}

std::string HTTP_Request::getBody(void) const
{
	if (this->request.method == POST)
		return (this->request.post.body);
	return ("");
}

std::map<std::string, std::string> HTTP_Request::getHeaders(void) const
{
	if (this->request.method == GET)
		return (this->request.get.headers);
	else if (this->request.method == POST)
		return (this->request.post.headers);
	else if (this->request.method == DELETE)
		return (this->request.delete_.headers);
	return (std::map<std::string, std::string>());
}