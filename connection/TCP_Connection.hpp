/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCP_connection.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:56:53 by amait-ou          #+#    #+#             */
/*   Updated: 2024/01/05 18:56:35 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TCP_CONNECTION
#define TCP_CONNECTION

#include "TCP_Exceptions.hpp"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>

typedef unsigned long t_ul;

class TCP_Connection: public TCP_Exception
{
	private:
		int socket_fd;
		struct sockaddr_in address_s;
	
	public:
		TCP_Connection(int domain, int service, int protocol,
			int port, t_ul interface);
};

#endif