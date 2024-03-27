/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCP_Exceptions.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:26:33 by amait-ou          #+#    #+#             */
/*   Updated: 2024/03/27 02:25:26 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TCP_Exception_HPP
#define TCP_Exception_HPP

#include <exception>

// TCP Exception Class
class TCP_Exception
{
	public:
		// Exception for Socket Creation
		class FailedToCreateSocket: public std::exception
		{
			public:
				virtual const char *what() const throw();
		};

		// Exception for Socket Binding
		class FailedToBindSocket: public std::exception
		{
			public:
				virtual const char *what() const throw();
		};

		// Exception for Socket Listening
		class FailedToListenForConnections: public std::exception
		{
			public:
				virtual const char *what() const throw();
		};

		// Exception for Socket Accepting
		class FailedToAcceptConnections: public std::exception
		{
			public:
				virtual const char *what() const throw();
		};

		// Exception for Socket Reading
		class FailedToSetOptions: public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
		
		class FailedToSetNonBlocking: public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
};

#endif