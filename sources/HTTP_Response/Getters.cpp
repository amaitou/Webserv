#include "../../includes/Respons.hpp"

// Getters 
int     Respons::getCurrentPort(void) const { return _currentPort; }

int     Respons::getStatusCode(void) const { return _statusCode; }

int     Respons::getClientFd(void) const { return _clientFd; }