/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Setters.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 03:58:18 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/10 06:48:03 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/HTTP_Request.hpp"

bool	HTTP_Request::addContent(char *content)
{
	this->content += std::string(content);
	if (this->checkGetRequest() || this->checkDeleteRequest()
		|| this->checkPostRequest())
		return (false);
	return (true);
}

void   HTTP_Request::setMethod(std::string &method)
{
	if (method == "GET")
		this->request.method = GET;
	else if (method == "POST")
		this->request.method = POST;
	else if (method == "DELETE")
		this->request.method = DELETE;
	else
		this->request.method = NONE;
}

void	HTTP_Request::setParams(std::string &path, std::string &query, std::string &version)
{
	this->request.path = path;
	if (path.find_last_of(".") != std::string::npos)
		this->request.extension = path.substr(path.find_last_of(".") + 1);
	else
		this->request.extension = "";
	this->request.version = version;
	this->request.query = query;
}

void	HTTP_Request::setBody(void)
{
	this->request.body = this->content.substr(this->content.find("\r\n\r\n") + 4);
}