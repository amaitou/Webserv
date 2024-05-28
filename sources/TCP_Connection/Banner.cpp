
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
