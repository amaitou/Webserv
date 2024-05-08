/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:02:08 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/08 10:45:54 by amait-ou         ###   ########.fr       */
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
					clients[this->client_fd].setClientFd(this->client_fd);
					clients[i].setClientFd(this->client_fd);
				}
				else
				{
					memset(buffer, 0, BUFFER_SIZE);
					read(i, buffer, BUFFER_SIZE);
					std::cout << GREEN << "___________ACCEPTED_REQUEST__________\n" << RESET << std::endl;
					std::cout << buffer << RESET << std::endl;
					clients[client_fd].request.initializeRequest(clients[client_fd].getClientFd(), buffer);
					std::cout << YELLOW << "___________CONTENT__________\n" << RESET << std::endl;
					std::cout << clients[client_fd].request.getContent() << "\n" << std::endl;
					std::cout << RED << "___________REQUEST_LINE__________\n" << RESET << std::endl;
					clients[client_fd].request.printRequestLine();
					if (clients[client_fd].request.getMethodType() == POST)
					{
						int val = clients[client_fd].request.parsePostRequest();
						while (val)
						{
							memset(buffer, 0, BUFFER_SIZE);
							read(client_fd, buffer, BUFFER_SIZE);
							clients[client_fd].request.setContent(buffer);
							val = clients[client_fd].request.parsePostRequest();
						}
						std::cout << GREEN << "___________BODY___________\n" << RESET << std::endl;
						clients[client_fd].request.printBody();
					}
					else if (clients[client_fd].request.getMethodType() == GET)
						clients[client_fd].request.parseGetRequest();
					else if (clients[client_fd].request.getMethodType() == DELETE)
						clients[client_fd].request.parseDeleteRequest();
					std::cout << GREY << "___________METHOD_TYPE____________\n" << RESET << std::endl;
					clients[client_fd].request.printMethodType();
					clients[client_fd].request.printPostMethodType();
					std::cout << BLUE << "___________HEADERS__________\n" << RESET << std::endl;
					clients[client_fd].request.printHeaders();
					FD_CLR(i, &this->fds.current_read_fds);
					FD_SET(i, &this->fds.current_write_fds);
				}
			}
			if (FD_ISSET(i, &this->fds.ready_write_fds))
			{
				send(i, http_res.c_str(), http_res.length(), 0);
				memset(buffer, 0, BUFFER_SIZE);
				clients[client_fd].request.cleanMembers();
				FD_CLR(i, &this->fds.current_write_fds);
				close(clients[client_fd].request.getFd());
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