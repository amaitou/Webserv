
#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include "TCP_Exceptions.hpp"
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <sstream>
#include <fcntl.h>
#include <string>
#include <map>

#define RED     "\x1B[31m"
#define BLUE    "\x1B[34m"
#define GREEN   "\x1B[32m"
#define GREY    "\x1B[90m"
#define CYAN	"\x1b[36m"
#define YELLOW  "\x1B[33m"
#define RESET   "\x1B[0m"

typedef enum e_method_type
{
	NONE,
	GET,
	POST,
	DELETE
}	t_method_type;

typedef struct s_request
{
	t_method_type	method;
	std::string		path;
	std::string		extension;
	std::string		query;
	std::string 	version;
	std::map<std::string, std::string> headers;
	std::string		body;
}	t_request;

class HTTP_Request
{
	private:
		std::string	content;
		t_request	request;
		int			fd;
	
	public:
		HTTP_Request(char *content);
		HTTP_Request(void);
		~HTTP_Request(void);

		t_method_type	getMethodType(void) const;
		std::string		getContent(void) const;
		std::string		getPath(void) const;
		std::string		getQuery(void) const;
		std::string		getVersion(void) const;
		std::string		getBody(void) const;
		std::map<std::string, std::string> getHeaders(void) const;
		std::string		getFileExtension(void) const;
		std::string		stringifyMethod(void) const;

		bool			addContent(char *, int &);
		void			setMethod(std::string &);
		void			setParams(std::string &, std::string &, std::string &);
		void			setBody(void);

		bool			checkCRLF(void) const;
		bool			checkGetRequest(void) const;
		bool			checkPostRequest(void) const;
		bool			checkDeleteRequest(void) const;
		bool			checkZeroCRLF(void) const;
		bool			checkChunked(void) const;
		bool			checkContentLength(void) const;

		void 			parseRequestLine(void);
		void			parseHeaders(void);
		void			parseBody(void);
		void			parseRequest(void);

		void			printRequestLine(void) const;
		void			printHeaders(void) const;
		void			printBody(void) const;
		void			printRequest(void) const;
};

#endif