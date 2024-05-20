/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Banner.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-amin <ael-amin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:05:09 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/20 12:10:42 by ael-amin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/TCP_Connection.hpp"

void TCP_Connection::displayBanner(void)
{
	const std::string green = "\033[0;32m";  // ANSI code for green text
	const std::string white = "\033[37m";

	std::cout << "\n\n" << std::endl;
	std::cout << "\t\t ██╗    ██╗███████╗██████╗ ███████╗███████╗██████╗ ██╗   ██╗" << std::endl;
	std::cout << green;
	std::cout << "\t\t ██║    ██║██╔════╝██╔══██╗██╔════╝██╔════╝██╔══██╗██║   ██║" << std::endl;
	std::cout << "\t\t ██║ █╗ ██║█████╗  ██████╔╝███████╗█████╗  ██████╔╝██║   ██║" << std::endl;
    std::cout << white;   // ANSI code to reset text color
	std::cout << "\t\t ██║███╗██║██╔══╝  ██╔══██╗╚════██║██╔══╝  ██╔══██╗╚██╗ ██╔╝" << std::endl;
	std::cout << green;
	std::cout << "\t\t ╚███╔███╔╝███████╗██████╔╝███████║███████╗██║  ██║ ╚████╔╝ " << std::endl;
	std::cout << "\t\t  ╚══╝╚══╝ ╚══════╝╚═════╝ ╚══════╝╚══════╝╚═╝  ╚═╝  ╚═══╝  " << std::endl;
	std::cout << "\n\n" << std::endl;
}
