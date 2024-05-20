/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_Instance.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:03:17 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/20 16:56:34 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "Config.hpp"
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

typedef struct s_socket
{
	_sockaddr_in				address_s;
	socklen_t					address_len;
	int							index;
	int							socket_fd;
} t_socket;

class Server
{
	private:

	public:
		Server(void);
		void	setSocketsNonBlocking(void);
		

		std::vector<t_socket>		sockets;
		int							index;
		Config						config;
};

#endif