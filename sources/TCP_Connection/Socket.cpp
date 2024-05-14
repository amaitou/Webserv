/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 04:09:41 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/14 18:52:09 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/TCP_Connection.hpp"

void	TCP_Connection::socketBind(void)
{
	std::cout << GREY << "[.] " << RESET << "Binding servers..." << std::endl;
	for (std::map<int, Server>::iterator it = servers.begin();
		it != servers.end(); it++)
	{
		int __bind = bind(it->second.getSocketFd(),
			(struct sockaddr *)&it->second.address_s, it->second.address_len);
		if (__bind < 0)
			throw TCP_Exception::FailedToBindSocket();
	}
	std::cout << YELLOW << "[+] " << RESET << "Servers were bound." << std::endl;
}

void	TCP_Connection::socketListen(void)
{
	for (std::map<int, Server>::iterator it = servers.begin();
		it != servers.end(); it++)
	{
		std::cout << GREEN << "[*] " << RESET << "Server ["
			<< it->second.index << "] is listening on port <"
			<< ntohs(it->second.address_s.sin_port) << ">" << std::endl;
		int __listen = listen(it->second.getSocketFd(), 10);
		if (__listen < 0)
			throw TCP_Exception::FailedToListenForConnections();
	}
	std::cout << "\n\n" << std::endl;
}

void	TCP_Connection::setSocketOptions(void)
{
	int opt = 1;
	for (std::map<int, Server>::iterator it = servers.begin();
		it != servers.end(); it++)
	{
		if (setsockopt(it->second.getSocketFd(), SOL_SOCKET, SO_REUSEADDR,
			&opt, sizeof(opt)) < 0)
			throw TCP_Exception::FailedToSetOptions();
	}
}