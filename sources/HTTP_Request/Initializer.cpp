/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Initializer.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 03:03:31 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/05 03:10:21 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/HTTP_Request.hpp"

void HTTP_Request::initializeRequest(int fd, char *buffer)
{
	this->setFd(fd);
	this->setNonBlocking();
	this->setContent(buffer);
	this->parseRequestLine();
}
