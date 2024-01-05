#include "TCP_Connection.hpp"

int main(void)
{
	try
	{
		const char *interface = "127.0.0.1";
		TCP_Connection http(AF_INET, SOCK_STREAM, 0, 80, inet_addr(interface));
	}
	catch (std::exception &e)
	{
		std::cerr << "Error " << e.what() << std::endl;
	}
}