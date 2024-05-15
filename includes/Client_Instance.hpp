/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 21:02:48 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/15 10:41:53 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HTTP_Request.hpp"

#ifndef CLIENT_HPP
#define CLIENT_HPP

class Client
{
	private:
		int client_fd;
		int server_fd;
		int	server_index;

	public:
		Client(void);
		Client(int &);

		void	setClientFd(int);
		void	setServerFd(int);
		void	setServerIndex(int);
		void	setClientNonBlocking(void);
		int		getClientFd(void) const;
		int		getServerFd(void) const;
		int		getServerIndex(void) const;
		
		HTTP_Request request;
};

#endif