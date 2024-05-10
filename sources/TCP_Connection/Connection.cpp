/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:02:08 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/10 09:47:20 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/TCP_Connection.hpp"

TCP_Connection::TCP_Connection(int domain, int service, int protocol, int port, t_ul interface)
{
	memset((char *)&address_s, 0, sizeof(address_s));
	memset(buffer, 0, BUFFER_SIZE);
	address_s.sin_family = domain;
	address_s.sin_port = htons(port);
	address_s.sin_addr.s_addr = htonl(interface);
	address_len = sizeof(address_s);
	this->server_fd = socket(domain, service, protocol);
	if (server_fd < 0)
		throw TCP_Exception::FailedToCreateSocket();
	this->setServerNonBlocking();
	this->setMultiplexer();
	
}

void TCP_Connection::socketAccept(void)
{
    while (true)
    {
		this->fds.ready_read_fds = this->fds.current_read_fds;
		this->fds.ready_write_fds = this->fds.current_write_fds;
		if (select(FD_SETSIZE, &this->fds.ready_read_fds, &this->fds.ready_write_fds, NULL, NULL) < 0)
		{
			std::cout << "Failed to select" << std::endl;
			continue;
		}
		for (int i = 0; i < FD_SETSIZE; i++)
		{
			if (FD_ISSET(i, &this->fds.ready_read_fds))
			{
				if (i == this->getServerFd())
				{
					if (this->addClient())
						std::cout << "Failed to add client" << std::endl;
				}
				else
					this->readClient(i);
			}
			else if (FD_ISSET(i, &this->fds.ready_write_fds))
				this->writeClient(i);
		}
    }
}

void TCP_Connection::serve(void)
{
	setSocketOptions();
	socketBind();
	socketListen();
	socketAccept();
}