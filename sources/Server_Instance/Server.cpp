/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:53:11 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/14 18:51:07 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

int		Server::getSocketFd(void) const
{
	return (this->server_fd);
}

void	Server::setSocketFd(int & fd)
{
	this->server_fd = fd;
}

Server::Server(void) {}

void Server::setServerNonBlocking(void)
{
	int flags = fcntl(server_fd, F_GETFL, 0);
	if (flags == -1)
		throw TCP_Exception::FailedToSetNonBlocking();
	if (fcntl(server_fd, F_SETFL, flags | O_NONBLOCK) == -1)
		throw TCP_Exception::FailedToSetNonBlocking();
}