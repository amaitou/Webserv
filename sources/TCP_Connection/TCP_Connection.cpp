/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCP_Connection.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:02:08 by amait-ou          #+#    #+#             */
/*   Updated: 2024/04/26 19:07:25 by amait-ou         ###   ########.fr       */
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

int TCP_Connection::getSocketFd(void) const
{
	return (server_fd);
}

socklen_t TCP_Connection::getAddressLen(void) const
{
	return (address_len);
}

struct sockaddr_in TCP_Connection::getStructSockAddrIn(void) const
{
	return (address_s);
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
        clients.setClientFd(client_fd);
        std::cout << YELLOW << "___________REQUEST__________\n" << RESET << std::endl;
        std::cout << buffer << RESET << std::endl;
        clients.request.initRequest(clients.getClientFd(), buffer);
        if (clients.request.getMethodType() == GET)
            clients.request.parseGetRequest();
        else if (clients.request.getMethodType() == POST)
            clients.request.parsePostRequest(buffer, BUFFER_SIZE);
        std::cout << CYAN << "___________REQUEST LINE__________\n" << RESET << std::endl;
        clients.request.printRequestLine();
        std::cout << GREEN << "___________HEADERS__________\n" << RESET << std::endl;
        clients.request.printHeaders();
        std::cout << GREY << "___________BODY__________\n" << RESET << std::endl;
        clients.request.printBody();
        send(client_fd, http_res.c_str(), http_res.length(), 0);
        memset(buffer, 0, BUFFER_SIZE);
        clients.request.cleanMembers();
        close(clients.request.getFd());
    }
}

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

void TCP_Connection::printListener(void) const
{
	std::cout 	<< "\n[.] "
				<< GREEN
				<< "Listening for upcoming connections on: \n"
				<< RESET
				<< "\n\t>> Port -> "
				<< GREEN
				<< ntohs(address_s.sin_port)
				<< RESET
				<< "\n\t>> Host -> "
				<< GREEN
				<< ntohs(address_s.sin_addr.s_addr)
				<< "\n"
				<< RESET
				<< std::endl;
}

void TCP_Connection::serve(void)
{
	socketSetOptions();
	socketBind();
	socketListen();
	socketAccept();
}