/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTP_Request.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 05:24:11 by amait-ou          #+#    #+#             */
/*   Updated: 2024/04/26 19:24:07 by amait-ou         ###   ########.fr       */
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
	GET,
	POST,
	DELETE,
	NONE
}	t_method_type;

// Enum for the type of the post request
typedef enum e_post_content_type
{
	CHUNKED_TRANSFER_ENCODING,
	MULTIPART_FORM_DATA,
	CUSTOM_DATA,
	_NONE
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
	std::string		path;
	std::string		query;
	std::string 	version;
	std::string		body;
	size_t			return_value;
	t_content_type	content_type;
	std::map<std::string, std::string> headers;
}	t_post_request;

// Struct for the request
typedef struct s_request
{
	t_method_type	method;
	t_get_request	get;
	t_post_request	post;
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

		// Initialize
		void			initRequest(int fd, char *buffer);

		// Getters
		t_method_type	getMethodType(void) const;
		std::string		getContent(void) const;
		int				getFd(void) const;

		// Setters
		void			setMethodType(t_method_type method);
		void			setContent(char *content);
		void			setFd(int fd);
		void			setNonBlocking(void);

		// Parser
		void			checkMethodType(void);
		void			parseRequestLine(void);
		int				parseGetRequest(void);

		void			parsePostRequest(char *buffer, int size);
		void			parseFullChunked(std::stringstream &ss);
		void			parseNonFullChunked(char *buffer, int size);
		void			parseContentLength(std::stringstream &ss, char *buffer, int size);
		void			setPostType(void);
		int				isContentLength(void) const;
		int				isChunked(void) const;
		int				isDataEnded(void) const;

		// Printers
		void			printRequestLine(void) const;
		void			printHeaders(void) const;
		void			printBody(void) const;
		void			printTypeOfPostRequest(void) const;

		// Cleaner
		void			cleanMembers(void);
};