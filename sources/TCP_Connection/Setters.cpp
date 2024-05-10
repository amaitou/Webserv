/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Setters.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 06:41:35 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/10 09:47:54 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/TCP_Connection.hpp"

void TCP_Connection::setSocketOptions(void)
{
	int		opt = 1;
	int __options = setsockopt(server_fd,
					SOL_SOCKET,
					SO_REUSEADDR,
					&opt,
					sizeof(opt));
	if (__options < 0)
		throw TCP_Exception::FailedToSetOptions();
}

void TCP_Connection::setServerNonBlocking(void)
{
	int flags = fcntl(this->getServerFd(), F_GETFL, 0);
	if (flags == -1)
		throw TCP_Exception::FailedToSetNonBlocking();
	if (fcntl(this->getServerFd(), F_SETFL, flags | O_NONBLOCK) == -1)
		throw TCP_Exception::FailedToSetNonBlocking();
}
