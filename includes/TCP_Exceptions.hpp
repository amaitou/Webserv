
#ifndef TCP_Exception_HPP
#define TCP_Exception_HPP

#include <exception>

// TCP Exception Class
class TCP_Exception
{
	public:
		class FailedToCreateSocket: public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
		class FailedToBindSocket: public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
		class FailedToListenForConnections: public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
		class FailedToAcceptConnections: public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
		class FailedToSetOptions: public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
		
		class FailedToSetNonBlocking: public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
};

#endif