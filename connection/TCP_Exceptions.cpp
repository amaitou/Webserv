/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCP_Exceptions.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:26:26 by amait-ou          #+#    #+#             */
/*   Updated: 2024/01/05 17:30:00 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TCP_Exceptions.hpp"

const char* TCP_Exception::FailedToCreateSocket::what() const throw()
{
    return ("Failed to create the socket");
}