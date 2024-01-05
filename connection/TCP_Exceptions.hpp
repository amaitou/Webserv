/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCP_EXceptions.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:26:33 by amait-ou          #+#    #+#             */
/*   Updated: 2024/01/05 17:36:57 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TCP_Exception_HPP
#define TCP_Exception_HPP

#include <exception>

class TCP_Exception
{
	public:
		class FailedToCreateSocket: public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
};

#endif