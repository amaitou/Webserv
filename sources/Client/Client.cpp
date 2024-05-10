/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 21:02:34 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/10 03:46:06 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Client.hpp"

Client::Client(void)
{
	this->fd = INT_MIN;
}

Client::Client(int fd)
{
	this->fd = fd;
}

void	Client::setClientFd(int fd)
{
	this->fd = fd;
	this->setClientNonBlocking();
}

int	Client::getClientFd(void) const
{
	return (this->fd);
}

void Client::setClientNonBlocking(void)
{
	int flags = fcntl(this->getClientFd(), F_GETFL, 0);
	if (flags == -1)
		throw TCP_Exception::FailedToSetNonBlocking();
	if (fcntl(this->getClientFd(), F_SETFL, flags | O_NONBLOCK) == -1)
		throw TCP_Exception::FailedToSetNonBlocking();
}