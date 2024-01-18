/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCP_Connection.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaitou <amaitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:56:53 by amait-ou          #+#    #+#             */
/*   Updated: 2024/01/18 00:01:38 by amaitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TCP_CONNECTION
#define TCP_CONNECTION

#include "TCP_Exceptions.hpp"
#include "HTTP_Request.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

#define RED     "\x1B[31m"
#define BLUE    "\x1B[34m"
#define GREEN   "\x1B[32m"
#define GREY    "\x1B[90m"
#define YELLOW  "\x1B[33m"
#define RESET   "\x1B[0m"

#define BUFFER_SIZE 1000

typedef unsigned long t_ul;
typedef struct sockaddr _sockaddr;
typedef struct sockaddr_in _sockaddr_in;

class TCP_Connection
{
	private:
		char			buffer[BUFFER_SIZE];
		int				server_fd;
		int				client_fd;
		HTTP_Request	Request;
		_sockaddr_in	address_s;
		socklen_t		address_len;
	
	public:
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
};

#endif