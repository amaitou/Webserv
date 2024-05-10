/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 21:02:48 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/10 03:11:04 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HTTP_Request.hpp"

#ifndef CLIENT_HPP
#define CLIENT_HPP

class Client
{
	private:
		int fd;

	public:
		Client(void);
		Client(int fd);

		void	setClientFd(int fd);
		void	setClientNonBlocking(void);
		int		getClientFd(void) const;
		
		HTTP_Request request;
};

#endif