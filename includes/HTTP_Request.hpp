/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTP_Request.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 05:24:11 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/14 17:08:39 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TCP_Exceptions.hpp"
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <string>
#include <fcntl.h>
#include <map>
#include <cstring>

#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

// Colors

#define RED     "\x1B[31m"
#define BLUE    "\x1B[34m"
#define GREEN   "\x1B[32m"
#define GREY    "\x1B[90m"
#define CYAN	"\x1b[36m"
#define YELLOW  "\x1B[33m"
#define RESET   "\x1B[0m"

// Enum for the type of the request
typedef enum e_method_type
{
	NONE,
	GET,
	POST,
	DELETE
}	t_method_type;

// Enum for the type of the post request
typedef enum e_post_content_type
{
	_NONE,
	RAW_BODY,
	MULTIPART_FORM_DATA,
	MULTIPART_DATA_FORM_WITH_CHUNKED_BODY,
	CHUNKED_BODY
}	t_content_type;

// Struct for the get request
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

		// Getters
		t_method_type	getMethodType(void) const;
		std::string		getContent(void) const;
		std::string		getPath(void) const;
		std::string		getQuery(void) const;
		std::string		getVersion(void) const;
		std::string		getBody(void) const;
		std::map<std::string, std::string> getHeaders(void) const;
		std::string		getFileExtension(void) const;
		std::string		stringifyMethod(void) const;

		// Setters
		bool			addContent(char *, int &);
		void			setMethod(std::string & method);
		void			setParams(std::string & path, std::string & query, std::string & version);
		void			setBody(void);

		// Checkers
		bool			checkCRLF(void) const;
		bool			checkGetRequest(void) const;
		bool			checkPostRequest(void) const;
		bool			checkDeleteRequest(void) const;
		bool			checkZeroCRLF(void) const;
		bool			checkChunked(void) const;
		bool			checkContentLength(void) const;

		// Parsers
		void 			parseRequestLine(void);
		void			parseHeaders(void);
		void			parseBody(void);
		void			parseRequest(void);

		// Printers
		void			printRequestLine(void) const;
		void			printHeaders(void) const;
		void			printBody(void) const;
		void			printRequest(void) const;
};

#endif