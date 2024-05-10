/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Getters.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 03:57:24 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/10 03:09:06 by amait-ou         ###   ########.fr       */
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

std::string	HTTP_Request::getPath(void) const
{
	return (this->request.path);
}

std::string HTTP_Request::getQuery(void) const
{
	return (this->request.query);
}

std::string HTTP_Request::getVersion(void) const
{
	return (this->request.version);
}

std::string HTTP_Request::getBody(void) const
{
	return (this->request.body);
}

std::map<std::string, std::string> HTTP_Request::getHeaders(void) const
{
	return (this->request.headers);
}

std::string HTTP_Request::getFileExtension(void) const
{
	return (this->request.extension);
}