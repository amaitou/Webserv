/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 03:45:06 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/05 03:45:08 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/TCP_Connection.hpp"

int main(void)
{
	try
	{
		system("clear");
		TCP_Connection HTTP(AF_INET, SOCK_STREAM, 0, 8080, INADDR_ANY);
		HTTP.serve();
	}
	catch (std::exception &e)
	{
		std::cerr << "Error " << e.what() << std::endl;
	}
}
