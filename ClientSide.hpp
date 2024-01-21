#ifndef CLIENTSIDE_HPP
#define CLIENTSIDE_HPP

#include "HTTP_Request.hpp"

class Client
{
    protected:
    
    public:
        HTTP_Request request;
        Client();
        Client(char *_request);
};

#endif