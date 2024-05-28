

#ifndef CLIENT_INSTANCE_HPP
#define CLIENT_INSTANCE_HPP

#include "HTTP_Request.hpp"
#include "HTTP_Respons.hpp"

class Client
{
	private:
		int			client_fd;
		int			server_fd;
		int			server_index;
		int			port;
		std::string ip;

	public:
		Client(void);
		Client(int &);

		void		setClientFd(int);
		void		setServerFd(int);
		void		setServerIndex(int);
		void		setPort(int);
		void		setIp(std::string);
		void		setClientNonBlocking(void);
		int			getClientFd(void) const;
		int			getServerFd(void) const;
		int			getServerIndex(void) const;
		int			getPort(void) const;
		std::string getIp(void) const;
		bool		writeResponse(void);
		
		HTTP_Request request;
		Respons respons;

		std::string responseContent;
		Config config;
};

#endif