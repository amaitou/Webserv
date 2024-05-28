
#include "../../includes/TCP_Exceptions.hpp"

const char* TCP_Exception::FailedToCreateSocket::what() const throw()
{
    return ("Failed to create the socket");
}

const char* TCP_Exception::FailedToBindSocket::what() const throw()
{
    return ("Failed to bind the socket");
}

const char* TCP_Exception::FailedToListenForConnections::what() const throw()
{
    return ("Failed to listen for connections");
}

const char* TCP_Exception::FailedToAcceptConnections::what() const throw()
{
    return ("Failed to accept connections");
}

const char* TCP_Exception::FailedToSetOptions::what() const throw()
{
    return ("Failed to set socket options");
}

const char* TCP_Exception::FailedToSetNonBlocking::what() const throw()
{
    return ("Failed to set socket to non-blocking mode");
}