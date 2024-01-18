#include "HTTP_Request.hpp"

HTTP_Request::HTTP_Request() {}

HTTP_Request::HTTP_Request(char *request)
{
    this->request = std::string(request);
    method.__method = _NONE;
}

std::string HTTP_Request::getPath(void) const
{
    return (method.__path);
}

std::string HTTP_Request::getVersion(void) const
{
    return (method.__version);
}

e_method HTTP_Request::getMethod(void) const
{
    return (method.__method);
}

void    HTTP_Request::setRequest(char *request)
{
    this->request = std::string(request);
}

std::map<std::string, std::string> HTTP_Request::getHeaders(void) const
{
    return (method.__headers);
}

void    HTTP_Request::parseRequest(void)
{
    std::string __method;
    std::string __request_line;

    std::istringstream stream(request);
    std::getline(stream, __request_line);
    std::istringstream(__request_line) >> __method >> method.__path >> method.__version; 
    if (__method == "GET")
        method.__method = _GET;
    else if (__method == "POST")
        method.__method = _POST;
    else if (__method == "DELETE")
        method.__method = _DELETE;
    else
        method.__method = _NONE;
    while (std::getline(stream, __request_line))
    {
        std::string _key;
        std::string _value;
        size_t position = __request_line.find(":");
        _key = __request_line.substr(0, position);
        _value = __request_line.substr(position + 2, __request_line.length());
        method.__headers.insert(std::make_pair(_key, _value));
    }
}