/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 21:02:34 by amait-ou          #+#    #+#             */
/*   Updated: 2024/04/26 18:57:38 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Client.hpp"

Client::Client(void)
{
	this->fd = INT_MIN;
}

Client::Client(int fd)
{
	this->fd = fd;
}

void	Client::setClientFd(int fd)
{
	this->fd = fd;
}

int	Client::getClientFd(void) const
{
	return (this->fd);
}