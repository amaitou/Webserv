/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Printers.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 04:10:48 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/04 04:10:52 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/TCP_Connection.hpp"

void TCP_Connection::printListener(void) const
{
	std::cout 	<< "\n[.] "
				<< GREEN
				<< "Listening for upcoming connections on: \n"
				<< RESET
				<< "\n\t>> Port -> "
				<< GREEN
				<< ntohs(address_s.sin_port)
				<< RESET
				<< "\n\t>> Host -> "
				<< GREEN
				<< ntohs(address_s.sin_addr.s_addr)
				<< "\n"
				<< RESET
				<< std::endl;
}