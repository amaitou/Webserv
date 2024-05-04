/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 04:09:41 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/04 04:11:29 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/TCP_Connection.hpp"

void TCP_Connection::socketSetOptions(void)
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

void	TCP_Connection::socketBind(void)
{
	int __bind = bind(server_fd, (struct sockaddr *)&(address_s), sizeof(address_s));
	if (__bind < 0)
		throw TCP_Exception::FailedToBindSocket();
}

void	TCP_Connection::socketListen(void)
{
	int __listen = listen(server_fd, 1);
	if (__listen < 0)
		throw TCP_Exception::FailedToListenForConnections();
	printListener();
}
