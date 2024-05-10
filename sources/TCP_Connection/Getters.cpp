/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Getters.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 04:08:37 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/10 09:47:38 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/TCP_Connection.hpp"

int TCP_Connection::getServerFd(void) const
{
	return (server_fd);
}

socklen_t TCP_Connection::getAddressLen(void) const
{
	return (address_len);
}

struct sockaddr_in TCP_Connection::getStructSockAddrIn(void) const
{
	return (address_s);
}
