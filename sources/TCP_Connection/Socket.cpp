
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
				std::cout << RED << "[-] " << RESET << "Failed to bind server "
					<< it->first << ": " << it->second.config.serverName() << " on port " << it->second.sockets[i].port << std::endl;
		}
	}
	std::cout << YELLOW << "[+] " << RESET << "Servers were bound." << std::endl;
}

void	TCP_Connection::socketListen(void)
{
	for (std::map<int, Server>::iterator it = servers.begin();
		it != servers.end(); it++)
	{
		std::cout << YELLOW << "[+] " << RESET << "Server " << it->first << " is listening on port ";
		for (size_t i = 0; i < it->second.config.listen().size(); i++)
		{
			if (listen(it->second.sockets[i].socket_fd, 100000) < 0)
				std::cout << RED << "[-] " << RESET << "Failed to listen on port "
					<< it->second.sockets[i].port << std::endl;
			if (i + 1 == it->second.config.listen().size())
				std::cout << it->second.config.listen()[i] << std::endl;
			else
				std::cout << it->second.config.listen()[i] << ", ";
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
				std::cout << RED << "[-] " << RESET << "Failed to bind server "
					<< it->first << " on port " << it->second.sockets[i].port << std::endl;
		}
	}
}