/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCP_Connection.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:56:53 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/20 22:44:39 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TCP_CONNECTION_HPP
#define TCP_CONNECTION_HPP

#include "./Server_Instance.hpp"
#include "./Client_Instance.hpp"
#include "./Config.hpp"
#include "./Parser.hpp"
#include <csignal>
#include <sys/time.h>
typedef struct fds
{
	fd_set						ready_read_fds;
	fd_set						ready_write_fds;
	fd_set						current_read_fds;
	fd_set						current_write_fds;
} 	t_fds;

#ifndef BUFFER_SIZE
	#define BUFFER_SIZE 1024
#endif

class TCP_Connection
{
	private:
			timeval						log_time;
			struct tm					*current_time;
			std::map<int, Server>		servers;
			std::map<int, Client>		clients;
			t_fds						fds;
			char						buffer[BUFFER_SIZE];

	public:
		TCP_Connection(std::vector<Config> &);

		void socketBind(void);
		void socketListen(void);
		void socketAccept(void);
		void setSocketOptions(void);
		void serversMonitoring(void);

		int		addClient(int &, int &);
		void	readClient(int &);
		void	writeClient(int &);
		void	ignoreSignPipe(int _signal);

		void 	displayBanner(void);

		void serve(void);
};

#endif
