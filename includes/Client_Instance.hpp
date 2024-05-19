/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client_Instance.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 21:02:48 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/19 21:36:29 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "HTTP_Request.hpp"
#include "HTTP_Respons.hpp"
// class Respons;
class Client
{
	private:
		int		client_fd;
		int		server_fd;
		int		server_index;

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
		bool	writeResponse(void);
		
		HTTP_Request request;
		Respons respons;

		std::string responseContent;
};

#endif