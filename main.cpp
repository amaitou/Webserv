#include "TCP_Connection.hpp"

int main(void)
{
	try
	{
		TCP_Connection HTTP(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY);
		HTTP.socketSetOptions();
		HTTP.socketBind();
		HTTP.socketListen();
		HTTP.socketAccept();
	}
	catch (std::exception &e)
	{
		std::cerr << "Error " << e.what() << std::endl;
	}
}