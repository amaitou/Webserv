/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCP_Connection.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:56:53 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/10 17:18:11 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TCP_CONNECTION_HPP
#define TCP_CONNECTION_HPP

#include "Client.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// Buffer Size for reading from socket

#ifndef BUFFER_SIZE
	#define BUFFER_SIZE 1024
#endif

// Typedefs for readability
typedef unsigned long t_ul;
typedef struct sockaddr _sockaddr;
typedef struct sockaddr_in _sockaddr_in;

// File Descriptors for select
typedef struct fds
{
	fd_set						ready_read_fds;
	fd_set						ready_write_fds;
	fd_set						current_read_fds;
	fd_set						current_write_fds;
} 	t_fds;

// TCP Connection Class
class TCP_Connection
{
	private:
		std::map<int, Client>			clients;
		char						buffer[BUFFER_SIZE];
		socklen_t					address_len;
		_sockaddr_in				address_s;
		int							server_fd;
		t_fds						fds;		
	
	public:
		// Constructors
		TCP_Connection(int domain, int service, int protocol, int port, t_ul interface);
		
		// Getters
		int				getServerFd(void) const;
		socklen_t		getAddressLen(void) const;
		_sockaddr_in	getStructSockAddrIn(void) const;
		
		// SysCalls
		void			socketBind(void);
		void			socketListen(void);
		void			socketAccept(void);

		// Setters
		void			setSocketOptions(void);
		void			setServerNonBlocking(void);

		// Printers
		void			printListener(void) const;
		void			printBanner(void) const;

		// Multiplexer
		void			setMultiplexer(void);
		int				addClient(void);
		void			readClient(int fd);
		void			writeClient(int fd);
		void			serversMonitoring(void);

		// Server
		void			serve(void);
};

#endif