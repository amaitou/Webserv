/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTP_Request.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 05:24:11 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/05 03:39:47 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TCP_Exceptions.hpp"
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <fcntl.h>
#include <map>

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
	REGULAR_CHUNKED_BODY,
	MULTIPART_FORM_DATA,
	MUTIPART_DATA_FORM_WITH_CHUNKED_BODY,
	REGULAR_BODY
}	t_content_type;

// Struct for the get request
typedef struct s_get_request
{
	std::string		path;
	std::string		query;
	std::string 	version;
	std::map<std::string, std::string> headers;
}	t_get_request;

// Struct for the post request
typedef struct s_post_request
{
	bool			return_value;
	std::string		path;
	std::string		query;
	std::string 	version;
	std::string		body;
	t_content_type	content_type;
	std::map<std::string, std::string> headers;
}	t_post_request;

typedef struct s_delete_request
{
	std::string		path;
	std::string		query;
	std::string 	version;
	std::map<std::string, std::string> headers;
}	t_delete_request;

// Struct for the request
typedef struct s_request
{
	t_method_type	method;
	t_get_request	get;
	t_post_request	post;
	t_delete_request delete_;
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

		// Initializers
		void			initializeRequest(int fd, char *buffer);

		// Getters
		t_method_type	getMethodType(void) const;
		std::string		getContent(void) const;
		int				getFd(void) const;
		std::string		getPath(void) const;
		std::string		getQuery(void) const;
		std::string		getVersion(void) const;
		std::string		getBody(void) const;
		std::map<std::string, std::string> getHeaders(void) const;
		t_content_type	getPostContentType(void) const;

		// Setters
		void			setFd(int fd);
		void			setNonBlocking(void);
		void			setContent(char *content);
		void			setMethodType(std::string &request_line);
		void			setPostContentType(void);

		// Checkers
		bool			checkCRLF(void) const;
		bool			checkContentLength(void) const;
		bool 			checkChunked(void) const;
		bool			checkMultipartDataForm(void) const;

		// Parsers
		int				parseRequestLine(void);
		void			setParamsOfRequestLine(std::string &path, std::string &query, std::string &version);
		int				parseGetRequest(void);
		int				parsePostRequest(void);
		int				parseDeleteRequest(void);
		void			parsePostHeaders(void);
		int 			parseRegularBody(std::string &content);
		int				parseChunkedBody(std::string &content);
		int				parseWhenDataIsCompleted(std::string &content);
		int				parseWhenDataIsNotCompleted(std::string &content);
		std::string		retrieveBodyFromChunkedData(void);

		// Printers
		void			printRequestLine(void) const;
		void			printHeaders(void) const;
		void			printBody(void) const;
		void			printMethodType(void) const;
		void			printPostMethodType(void) const;

		// Cleaners
		void			cleanMembers(void);
};