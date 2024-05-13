/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 03:45:06 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/13 17:46:54 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/TCP_Connection.hpp"

int main(int ac, char **ag)
{
	try
	{
		if (ac != 2)
			throw std::runtime_error("Usage: ./webserv [config_file]");
		system("clear");
		int checkError = 0;
		std::cout << GREY << "[.] " << RESET << "Parsing configuration file..." << RESET << std::endl;
		std::vector<Config>	servers = getConfig(ag[1], &checkError);
		std::cout << YELLOW << "[+] " << RESET << "Configuration file was parsed." << RESET << std::endl;
		TCP_Connection HTTP(servers);
		HTTP.serve();
	}
	catch (std::exception &e)
	{
		std::cerr << "Error " << e.what() << std::endl;
	}
}
