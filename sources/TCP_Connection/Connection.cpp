/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:02:08 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/10 05:33:19 by amait-ou         ###   ########.fr       */
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
	this->setSocketNonBlocking();
	FD_ZERO(&this->fds.current_read_fds);
	FD_ZERO(&this->fds.current_write_fds);
	FD_SET(server_fd, &this->fds.current_read_fds);
	FD_SET(server_fd, &this->fds.current_write_fds);
	
}

void TCP_Connection::socketAccept(void)
{
    std::string p = "<h1>Response Has Been Sent Successfully</h1>";
    std::string http_res = "HTTP/1.1 200 OK Content-Type: text/html\nContent-Length:" + std::to_string(p.length()) + "\n\n" + p + "\n";

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
				if (i == this->getSocketFd())
				{
					std::cout << "New Connection\n" << std::endl;
					this->client_fd = accept(this->getSocketFd(), (struct sockaddr *)&address_s, &address_len);
					if (this->client_fd < 0)
					{
						std::cout << "Failed to accept connection" << std::endl;
						continue;  
					}
					FD_SET(this->client_fd, &this->fds.current_read_fds);
					clients[client_fd] = Client(client_fd);
				}
				else
				{
					memset(buffer, 0, BUFFER_SIZE);
					read(i, buffer, BUFFER_SIZE);
					int v = this->clients[i].request.addContent(buffer);
					if (!v)
					{
						clients[i].request.parseRequest();
						clients[i].request.printRequest();
						FD_CLR(i, &this->fds.current_read_fds);
						FD_SET(i, &this->fds.current_write_fds);
					}
				}
			}
			else if (FD_ISSET(i, &this->fds.ready_write_fds))
			{
				write(i, http_res.c_str(), http_res.length());
				memset(buffer, 0, BUFFER_SIZE);
				FD_CLR(i, &this->fds.current_write_fds);
				close(i);
			}
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