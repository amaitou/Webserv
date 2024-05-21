/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Multiplexer.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 09:33:46 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/21 18:48:03 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/TCP_Connection.hpp"

CGI_Response*	TCP_Connection::get_cgi_read(int fd) {
	std::vector<CGI_Response*>::iterator it = cgi_responses.begin();
	while (it != cgi_responses.end()) {
		CGI_Response* res = *it;

		if (res->fd_read == fd)
			return res;

		++it;
	}
	return NULL;
}
CGI_Response*	TCP_Connection::get_cgi_write(int fd) {
	std::vector<CGI_Response*>::iterator it = cgi_responses.begin();
	while (it != cgi_responses.end()) {
		CGI_Response* res = *it;

		if (res->fd_write == fd)
			return res;
		
		++it;
	}
	return NULL;
}

int		TCP_Connection::addClient(int & fd, int & index)
{
	int client_fd = -1;
	size_t tracker = 0;
	for (size_t i = 0; i < this->servers[index].sockets.size(); i++)
	{
		tracker = i;
		if (this->servers[index].sockets[i].socket_fd == fd)
		{
			client_fd = accept(this->servers[index].sockets[i].socket_fd,
				(struct sockaddr *)&this->servers[index].sockets[i].address_s,
				&this->servers[index].sockets[i].address_len);
			if (client_fd < 0)
				TCP_Exception::FailedToAcceptConnections();
			break;
		}
	}
	std::cout << CYAN << "- " << "[" << current_time->tm_hour
		<< ":" << current_time->tm_min << ":"
		<< current_time->tm_sec << "] "
		<<  "- Webserv += " << RESET
		<< "[server " << this->servers[index].index
		<< "], [" << this->servers[index].config.ip()
		<< ":" <<  this->servers[index].sockets[tracker].port
		<< "] - " << "new client connected."
		<< std::endl;
	FD_SET(client_fd, &this->fds.current_read_fds);
	this->clients[client_fd].setClientFd(client_fd);
	this->clients[client_fd].config = this->servers[index].config;
	this->clients[client_fd].setPort(this->servers[index].sockets[tracker].port);
	this->clients[client_fd].setIp(this->servers[index].config.ip());
	std::pair<int, Client> pair(client_fd, Client(client_fd));
	this->clients[client_fd].setServerFd(this->servers[index].sockets[tracker].socket_fd);
	this->clients[client_fd].setServerIndex(index);
	this->clients.insert(pair);
	return (0);
}

void	TCP_Connection::readClient(int & fd)
{
	memset(this->buffer, 0, BUFFER_SIZE);
	int r = read(fd, this->buffer, BUFFER_SIZE);
	this->buffer[r] = '\0';
	int v = this->clients[fd].request.addContent(this->buffer, r);
	if (!v)
	{
		this->clients[fd].request.parseRequest();
		std::cout << GREEN << "- " << "[" << current_time->tm_hour
			<< ":" << current_time->tm_min << ":"
			<< current_time->tm_sec << "] "
			<< "- Webserv >> " << RESET
			<< "[server " << this->clients[fd].getServerIndex()
			<< "], [" << this->clients[fd].getIp()
			<< ":" << this->clients[fd].getPort()
			<< "] - request received Successfully, [method <"
			<< this->clients[fd].request.stringifyMethod()
			<< ">], [target <" << this->clients[fd].request.getPath()
			<< ">]." << RESET << std::endl;
		FD_CLR(fd, &this->fds.current_read_fds);
		FD_SET(fd, &this->fds.current_write_fds);
	}
}

bool TCP_Connection::client_has_cgi(int fd)
{
	std::vector<CGI_Response*>::iterator it = cgi_responses.begin();
	while (it != cgi_responses.end()) {
		CGI_Response* res = *it;

		if (res->fd_client == fd)
			return res->is_done();
	}
	return false;
}

void	TCP_Connection::writeClient(int & fd)
{
	bool clientHasCGI = client_has_cgi(fd);
	if (clients[fd].responseContent.length() == 0 && !clientHasCGI)
	{
		Result result = clients[fd].respons.sendRespons(clients[fd], this->clients[fd].config);
		if (result.cgi_response == NULL)
			this->clients[fd].responseContent = result.responseContent;
			
		else {
			CGI_Response* res = result.cgi_response;
			// std::cout << "cgi response for client: " << res->fd_client << std::endl;
			FD_SET(res->fd_read, &fds.current_read_fds);
			FD_SET(res->fd_write, &fds.current_write_fds);
			FD_CLR(res->fd_client, &fds.current_read_fds);
			FD_CLR(res->fd_client, &fds.current_write_fds);
			cgi_responses.push_back(res);
			// std::cout << "returning" << std::endl;
			return;
		}
	}
	else if (clientHasCGI) return;

	bool b = this->clients[fd].writeResponse();
	if (!b)
	{
		std::cout << YELLOW << "- " << "[" << current_time->tm_hour
			<< ":" << current_time->tm_min << ":"
			<< current_time->tm_sec << "] "
			<< "- Webserv << " << RESET
			<< "[server " << this->clients[fd].getServerIndex()
			<< "], [" << this->clients[fd].getIp()
			<< ":" << this->clients[fd].getPort()
			<< "] - response sent Successfully." << std::endl;
		FD_CLR(fd, &this->fds.current_write_fds);
		std::cout << RED << "- " << "[" << current_time->tm_hour
			<< ":" << current_time->tm_min << ":"
			<< current_time->tm_sec << "] "
			<<  "- Webserv -= " << RESET
			<< "[server " << this->clients[fd].getServerIndex()
			<< "], [" << this->clients[fd].getIp()
			<< ":" << this->clients[fd].getPort()
			<< "] - client disconnected." << std::endl;
		this->clients.erase(fd);
		// std::cout << "closing: " << fd << std::endl;
		close(fd);
	}
	memset(this->buffer, 0, BUFFER_SIZE);
}

void	TCP_Connection::serversMonitoring(void)
{
	std::cout << GREY << "[^] " << RESET << "Monitoring servers :\n" << std::endl;
	while (true)
    {
		this->ignoreSIGPIPE(SIGPIPE);
		this->fds.ready_read_fds = this->fds.current_read_fds;
		this->fds.ready_write_fds = this->fds.current_write_fds;

		gettimeofday(&this->log_time, NULL);
		this->current_time = localtime(&this->log_time.tv_sec);

		int r = select(FD_SETSIZE, &this->fds.ready_read_fds, &this->fds.ready_write_fds, NULL, NULL);
		if (r < 0)
			std::cout << "Failed to select" << std::endl;
		
		for (int i = 0; i < FD_SETSIZE && r > 0; ++i)
		{
			// if cgi read
			// if (FD_ISSET(i, &fds.ready_read_fds) || FD_ISSET(i, &fds.ready_write_fds))
			// 	std::cout << i << std::endl;
				
			CGI_Response* res_read = this->get_cgi_read(i);
			CGI_Response* res_write = this->get_cgi_write(i);
			if (res_read) {
				if (!FD_ISSET(res_read->fd_read, &fds.ready_read_fds))
					continue;
				if (res_read->readCgi())
                {
                    int fd = res_read->fd_client;
		            this->clients[fd].responseContent = res_read->getResponsContent();
					
					std::vector<CGI_Response*>::iterator it = std::find(cgi_responses.begin(), cgi_responses.end(), res_read);
					cgi_responses.erase(it);
					FD_CLR(res_read->fd_read, &fds.current_read_fds);
					FD_CLR(res_read->fd_write, &fds.current_write_fds);
					FD_CLR(res_read->fd_read, &fds.ready_read_fds);
					FD_CLR(res_read->fd_write, &fds.ready_write_fds);
					FD_SET(res_read->fd_client, &fds.current_write_fds);
					delete res_read;
                }
			}
			// else if cgi write
			else if ( res_write ) {
				if (!FD_ISSET(res_write->fd_write, &fds.ready_write_fds))
					continue;
				res_write->writeCgi();
			}
			else if (FD_ISSET(i, &this->fds.ready_read_fds))
			{
				// std::cout << "read normal request" << std::endl;
				for (std::map<int, Server>::iterator it = this->servers.begin();
					it != this->servers.end(); ++it)
				{
					for (size_t j = 0; j < it->second.sockets.size(); j++)
					{
						if (i == it->second.sockets[j].socket_fd)
						{
							int index = it->first;
							if (this->addClient(i, index))
								break;
						}
					}
				}
				if (this->clients.find(i) != this->clients.end())
					this->readClient(i);

			}
			else if (FD_ISSET(i, &this->fds.ready_write_fds)) {
				// std::cout << "write normal response" << std::endl;
				this->writeClient(i);
				// std::cout << "wrote client" << std::endl;
			}
		}
    }
}
