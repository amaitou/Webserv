#ifndef CGI_HPP
#define CGI_HPP

#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <vector>
#include <sstream>
#include <signal.h>
#include <map>
#include <cstdlib>
#include <ctime>

class CgiHandler
{
	private:
		std::string cgiPath;
		std::string requestMethod;
		std::string cgiExtention;
		std::string responseBody;
		std::string requestBody;
		int         statusCode;
		pid_t       cgiPid;
		time_t      startTime;
		std::map<std::string, std::string> headers;

		void executeCgi();

	public:
		CgiHandler(std::string _path, std::string _method, std::string _extension, std::string _body , std::map<std::string, std::string> _headers);
		~CgiHandler();

		int             getStatusCode() const;
		std::string     getResponseBody() const;
		void            handleRequest();
		void            checkTimeout();
};

#endif
