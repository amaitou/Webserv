/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 04:09:41 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/20 16:58:07 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/TCP_Connection.hpp"

void	TCP_Connection::socketBind(void)
{
	std::cout << GREY << "[.] " << RESET << "Binding servers..." << std::endl;
	for (std::map<int, Server>::iterator it = servers.begin();
		it != servers.end(); it++)
	{
		for (size_t i = 0; i < it->second.config.listen().size(); i++)
		{
			if (bind(it->second.sockets[i].socket_fd,
				(struct sockaddr *)&it->second.sockets[i].address_s,
				it->second.sockets[i].address_len) < 0)
				throw TCP_Exception::FailedToBindSocket();
		}
	}
	std::cout << YELLOW << "[+] " << RESET << "Servers were bound." << std::endl;
}

void	TCP_Connection::socketListen(void)
{
	for (std::map<int, Server>::iterator it = servers.begin();
		it != servers.end(); it++)
	{
		for (size_t i = 0; i < it->second.config.listen().size(); i++)
		{
			if (listen(it->second.sockets[i].socket_fd, it->second.config.listen().size()) < 0)
				throw TCP_Exception::FailedToListenForConnections();
		}
	}
	std::cout << "\n\n" << std::endl;
}

void	TCP_Connection::setSocketOptions(void)
{
	int opt = 1;
	for (std::map<int, Server>::iterator it = servers.begin();
		it != servers.end(); it++)
	{
		for (size_t i = 0; i < it->second.config.listen().size(); i++)
		{
			if (setsockopt(it->second.sockets[i].socket_fd, SOL_SOCKET, SO_REUSEADDR,
				&opt, sizeof(opt)) < 0)
				throw TCP_Exception::FailedToSetOptions();
		}
	}
}