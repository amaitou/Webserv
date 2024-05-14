/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCP_Connection.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:56:53 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/14 11:04:21 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TCP_CONNECTION_HPP
#define TCP_CONNECTION_HPP

#include "../includes/Server.hpp"
#include "../includes/Config.hpp"
#include "../includes/Parser.hpp"

// File Descriptors for select
typedef struct fds
{
	fd_set						ready_read_fds;
	fd_set						ready_write_fds;
	fd_set						current_read_fds;
	fd_set						current_write_fds;
} 	t_fds;

// Buffer Size for reading from socket
#ifndef BUFFER_SIZE
	#define BUFFER_SIZE 1024
#endif

// TCP Connection Class
class TCP_Connection
{
	private:
			std::map<int, Server> servers;
			std::map<int, Client>		clients;
			t_fds						fds;
			char						buffer[BUFFER_SIZE];

	public:
		TCP_Connection(std::vector<Config> &config);

		void socketBind(void);
		void socketListen(void);
		void socketAccept(void);
		void setSocketOptions(void);
		void serversMonitoring(void);

		int		addClient(int fd);
		void	readClient(int fd);
		void	writeClient(int fd);

		void 	displayBanner(void);

		void serve(void);
};

#endif