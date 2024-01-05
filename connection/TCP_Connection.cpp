/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCP_Connection.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:02:08 by amait-ou          #+#    #+#             */
/*   Updated: 2024/01/05 18:57:14 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TCP_Connection.hpp"

TCP_Connection::TCP_Connection(int domain, int service, int protocol,
	int port, t_ul interface)
{
	// Initialize the address to 0
	memset(&this->address_s, 0, sizeof(this->address_s));
	// Set address family to AF_INET (IPv4)
	this->address_s.sin_family = domain;
	// Set the port using the htons (host to network short "Big Endian")
	this->address_s.sin_port = htons(port);
	// Set the IP address again using htons to convert the IP to Big Endian
	this->address_s.sin_addr.s_addr = htonl(interface);
	// Create our socket file descriptor
	this->socket_fd = socket(domain, service, protocol);
	// Check if the socket is created successfully
	if (this->socket_fd < 0)
		throw TCP_Connection::TCP_Exception::FailedToCreateSocket();
}