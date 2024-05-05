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