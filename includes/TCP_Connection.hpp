/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCP_Connection.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:56:53 by amait-ou          #+#    #+#             */
/*   Updated: 2024/03/22 03:57:39 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TCP_CONNECTION_HPP
#define TCP_CONNECTION_HPP

#include "TCP_Exceptions.hpp"
#include "HTTP_Request.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

// Colors

#define RED     "\x1B[31m"
#define BLUE    "\x1B[34m"
#define GREEN   "\x1B[32m"
#define GREY    "\x1B[90m"
#define CYAN	"\x1b[36m"
#define YELLOW  "\x1B[33m"
#define RESET   "\x1B[0m"

// Buffer Size for reading from socket

#define BUFFER_SIZE 1024

// Typedefs for readability

typedef unsigned long t_ul;
typedef struct sockaddr _sockaddr;
typedef struct sockaddr_in _sockaddr_in;

// TCP Connection Class

class TCP_Connection
{
	private:
		char			buffer[BUFFER_SIZE];
		int				server_fd;
		int				client_fd;
		_sockaddr_in	address_s;
		socklen_t		address_len;
		HTTP_Request	request;
		
	
	public:
		// Constructors
		TCP_Connection(int domain, int service, int protocol, int port, t_ul interface);
		
		// Getters
		int				getSocketFd(void) const;
		socklen_t		getAddressLen(void) const;
		_sockaddr_in	getStructSockAddrIn(void) const;
		
		// SysCalls
		void			socketBind(void);
		void			socketListen(void);
		void			socketAccept(void);

		// Setters
		void			socketSetOptions(void);

		// Printers
		void			printListener(void) const;
		void			printBanner(void) const;

		// Server
		void			serve(void);
};

#endif