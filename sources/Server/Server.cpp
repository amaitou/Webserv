/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:53:11 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/14 10:42:14 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

int		Server::getServerFd(void) const
{
	return (this->server_fd);
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

int		Server::getServerIndex(void) const
{
	return (this->index);
}