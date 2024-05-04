/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Getters.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 03:57:24 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/04 03:57:51 by amait-ou         ###   ########.fr       */
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