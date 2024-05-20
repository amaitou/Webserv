/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:53:11 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/20 16:54:57 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server_Instance.hpp"
#include "../../includes/TCP_Exceptions.hpp"
#include <fcntl.h>

Server::Server(void) {}

void Server::setSocketsNonBlocking(void)
{
	for (size_t i = 0; i < this->sockets.size(); i++)
	{
		if (fcntl(this->sockets[i].socket_fd, F_SETFL, O_NONBLOCK) < 0)
			throw TCP_Exception::FailedToSetNonBlocking();
	}
}