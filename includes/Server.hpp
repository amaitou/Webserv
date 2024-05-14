/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:03:17 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/14 10:43:06 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

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

class Server
{	
	public:
		// Constructors
		Server(void);
		Server(int domain, int service, std::vector<int> ports, t_ul interface);

		// Getters
		int							getServerFd(void) const;
		std::vector<int>			getPorts(void) const;

		// Setters
		void						setServerNonBlocking(void);

		// Setters
		void						setSocketOptions(void);

		_sockaddr_in				address_s;
		socklen_t					address_len;
		int							server_fd;
		int							index;
};

#endif