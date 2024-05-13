/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Setters.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:17:04 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/12 19:35:29 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

Server::Server(void) {}

void Server::setServerNonBlocking(void)
{
	int flags = fcntl(server_fd, F_GETFL, 0);
	if (flags == -1)
		throw TCP_Exception::FailedToSetNonBlocking();
	if (fcntl(server_fd, F_SETFL, flags | O_NONBLOCK) == -1)
		throw TCP_Exception::FailedToSetNonBlocking();
}
