/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCP_Exceptions.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:26:26 by amait-ou          #+#    #+#             */
/*   Updated: 2024/03/27 02:25:32 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/TCP_Exceptions.hpp"

const char* TCP_Exception::FailedToCreateSocket::what() const throw()
{
    return ("Failed to create the socket");
}

const char* TCP_Exception::FailedToBindSocket::what() const throw()
{
    return ("Failed to bind the socket");
}

const char* TCP_Exception::FailedToListenForConnections::what() const throw()
{
    return ("Failed to listen for connections");
}

const char* TCP_Exception::FailedToAcceptConnections::what() const throw()
{
    return ("Failed to accept connections");
}

const char* TCP_Exception::FailedToSetOptions::what() const throw()
{
    return ("Failed to set socket options");
}

const char* TCP_Exception::FailedToSetNonBlocking::what() const throw()
{
    return ("Failed to set socket to non-blocking mode");
}