#include "ClientSide.hpp"

Client::Client() {}
Client::Client(char *_request)
{
    request.setRequest(_request);
}