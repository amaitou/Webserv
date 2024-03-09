/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTP_Request.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaitou <amaitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 05:24:11 by amait-ou          #+#    #+#             */
/*   Updated: 2024/03/09 04:04:51 by amaitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
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
	CHUNKED,
	BODY,
	BOUNDRY,
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
	
	public:
		HTTP_Request(char *content);
		HTTP_Request(void);
		~HTTP_Request(void);

		// Getters
		t_method_type	getMethodType(void) const;
		std::string		getContent(void) const;

		// Setters
		void			setMethodType(t_method_type method);
		void			setContent(char *content);

		// Parser
		void			checkMethodType(void);
		void			parseRequestLine(void);
		int				parseGetRequest(void);

		// Printers

		void	printRequestLine(void) const;
		void	printHeaders(void) const;
		void	printBody(void) const;

		// Cleaner
		void cleanMembers(void);
};