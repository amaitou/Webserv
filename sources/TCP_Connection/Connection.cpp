/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:02:08 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/06 04:22:10 by amait-ou         ###   ########.fr       */
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
	server_fd = socket(domain, service, protocol);
	if (server_fd < 0)
		throw TCP_Exception::FailedToCreateSocket();
}

void TCP_Connection::socketAccept(void)
{
    std::string p = "<h1>Response Has Been Sent Successfully</h1>";
    std::string http_res = "HTTP/1.1 200 OK Content-Type: text/html\nContent-Length:" + std::to_string(p.length()) + "\n\n" + p + "\n";

    while (true)
    {
        int client_fd = accept(this->getSocketFd(), (struct sockaddr *)&address_s, &address_len);
        if (client_fd < 0)
        {
            std::cout << "Failed to accept connection" << std::endl;
            continue;  
        }
        read(client_fd, buffer, BUFFER_SIZE);
        clients[client_fd].setClientFd(client_fd);
        std::cout << GREEN << "___________ACCEPTED_REQUEST__________\n" << RESET << std::endl;
        std::cout << buffer << RESET << std::endl;
        clients[client_fd].request.initializeRequest(clients[client_fd].getClientFd(), buffer);
        std::cout << YELLOW << "___________CONTENT__________\n" << RESET << std::endl;
		std::cout << clients[client_fd].request.getContent() << "\n" << std::endl;
		std::cout << RED << "___________REQUEST_LINE__________\n" << RESET << std::endl;
		clients[client_fd].request.printRequestLine();
		if (clients[client_fd].request.getMethodType() == POST)
		{
			if (!clients[client_fd].request.parsePostRequest())
			{
				std::cout << GREEN << "___________BODY___________\n" << RESET << std::endl;
				clients[client_fd].request.printBody();
			}
			else
			{
				while (clients[client_fd].request.parsePostRequest())
				{
					memset(buffer, 0, BUFFER_SIZE);
					read(client_fd, buffer, BUFFER_SIZE);
					clients[client_fd].request.setContent(buffer);
				}
				std::cout << GREEN << "___________BODY___________\n" << RESET << std::endl;
				clients[client_fd].request.printBody();
			}
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
        send(client_fd, http_res.c_str(), http_res.length(), 0);
        memset(buffer, 0, BUFFER_SIZE);
        clients[client_fd].request.cleanMembers();
        close(clients[client_fd].request.getFd());
    }
}

void TCP_Connection::serve(void)
{
	socketSetOptions();
	socketBind();
	socketListen();
	socketAccept();
}