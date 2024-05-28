
#include "../includes/TCP_Connection.hpp"

int main(int ac, char **ag)
{
	std::vector<Config>	servers;
	try
	{
		int checkError = 0;
		std::cout << GREY << "[.] " << RESET << "Parsing configuration file..." << RESET << std::endl;
		if (ac > 1)
			servers = getConfig(ag[1], &checkError);
		else
			servers = getConfig("", &checkError);
		if (checkError)
			return 1;
		std::cout << YELLOW << "[+] " << RESET << "Configuration file was parsed." << RESET << std::endl;
		TCP_Connection HTTP(servers);
		HTTP.serve();
	}
	catch (std::exception &e)
	{
		std::cerr << "Error " << e.what() << std::endl;
	}
	return (EXIT_SUCCESS);
}
