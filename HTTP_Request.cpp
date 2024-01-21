/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTP_Request.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 05:40:53 by amait-ou          #+#    #+#             */
/*   Updated: 2024/01/21 18:43:09 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HTTP_Request.hpp"

HTTP_Request::HTTP_Request() {}

HTTP_Request::HTTP_Request(char *request)
{
    memset((char *)&method, 0, sizeof(method));
    this->request = std::string(request);
    methodType = _NONE;
}

e_method HTTP_Request::getMethodType(void) const
{
    return (methodType);
}

std::string HTTP_Request::getGetPath(void) const
{
    return (method.__get.__path);
}

std::string HTTP_Request::getGetVersion(void) const
{
    return (method.__get.__version);
}

std::string HTTP_Request::getGetQuery(void) const
{
    return (method.__get.__query);
}

std::map<std::string, std::string> HTTP_Request::getGetHeaders(void) const
{
    return (method.__get.__headers);
}

std::string HTTP_Request::getPostPath(void) const
{
    return (method.__post.__path);
}

std::string HTTP_Request::getPostVersion(void) const
{
    return (method.__post.__version);
}

std::string HTTP_Request::getPostQuery(void) const
{
    return (method.__post.__query);
}

std::string HTTP_Request::getPostBody(void) const
{
    return (method.__post.__body);
}

std::map<std::string, std::string> HTTP_Request::getPostHeaders(void) const
{
    return (method.__post.__headers);
}

void    HTTP_Request::setRequest(char *request)
{
    this->request = std::string(request);
}

void    HTTP_Request::parseRequest(void)
{
    std::string request_line;

    std::string _method;
    std::string _version;
    std::string _path;

    std::stringstream stream(request);
    std::getline(stream, request_line);
    std::stringstream __temp(request_line);

    __temp >> _method >> _path >> _version;
    if (_method == "GET")
    {
        method.__get.__version = _version;
        parseGet(_path, stream, request_line);
    }
    else if (_method == "POST")
    {
        method.__post.__version = _version;
        parsePost(_path, stream, request_line);
    }
    else if (_method == "DELETE")
        methodType = _DELETE;
    else
        methodType = _NONE;
}

void    HTTP_Request::parseGet(std::string &__temp_path, std::stringstream &stream, std::string &__request_line)
{
    methodType = _GET;
    if (__temp_path.find("?") != std::string::npos)
    {
        size_t position = __temp_path.find("?");
        method.__get.__path = __temp_path.substr(0, position);
        method.__get.__query = __temp_path.substr(position + 1, __temp_path.length());
    }
    else
    {
        method.__get.__path = __temp_path;
        method.__get.__query = "";
    }
    while (std::getline(stream, __request_line))
    {
        std::string _key;
        std::string _value;
        if (__request_line == "\r")
            break;
        size_t position = __request_line.find(":");
        _key = __request_line.substr(0, position);
        if (_key.find("\r") != std::string::npos)
            _key = _key.substr(0, _key.find("\r"));
        _value = __request_line.substr(position + 2, __request_line.length());
        if (_value.find("\r") != std::string::npos)
            _value = _value.substr(0, _value.find("\r"));
        method.__get.__headers.insert(std::make_pair(_key, _value));
    }
}

void    HTTP_Request::parsePost(std::string &__temp_path, std::stringstream &stream, std::string &__request_line)
{
    methodType = _POST;
    if (__temp_path.find("?") != std::string::npos)
    {
        size_t position = __temp_path.find("?");
        method.__post.__path = __temp_path.substr(0, position);
        method.__post.__query = __temp_path.substr(position + 1, __temp_path.length());
    }
    else
    {
        method.__post.__path = __temp_path;
        method.__post.__query = "";
    }
    while (std::getline(stream, __request_line) && __request_line != "\r")
    {
        std::string _key;
        std::string _value;

        size_t position = __request_line.find(":");
        _key = __request_line.substr(0, position);
        if (_key.find("\r") != std::string::npos)
            _key = _key.substr(0, _key.find("\r"));
        _value = __request_line.substr(position + 2, __request_line.length());
        if (_value.find("\r") != std::string::npos)
            _value = _value.substr(0, _value.find("\r"));
        method.__post.__headers.insert(std::make_pair(_key, _value));
    }
    if (checkChunkedData())
    {
        std::getline(stream, __request_line);
        parsePostChunkedData(stream, __request_line);
    }
    else
    {
        while (std::getline(stream, __request_line))
        {
            if (__request_line.find("\r") != std::string::npos)
                __request_line = __request_line.substr(0, __request_line.find("\r"));
            method.__post.__body += __request_line;
        }
    }
}

void    HTTP_Request::parsePostChunkedData(std::stringstream &stream, std::string &__request_line)
{
    while (std::getline(stream, __request_line))
    {
        if (__request_line.find("\\r") != std::string::npos)
            __request_line = __request_line.substr(0, __request_line.find("\\r"));
        if (__request_line == "0")
            break;
        std::getline(stream, __request_line);
        if (__request_line.find("\\r") != std::string::npos)
            __request_line = __request_line.substr(0, __request_line.find("\\r"));
        method.__post.__body += __request_line;
    }
}

bool HTTP_Request::checkChunkedData(void)
{
    if (methodType == _POST)
    {
        if (method.__post.__headers.find("Transfer-Encoding") != method.__post.__headers.end()
            && method.__post.__headers["Transfer-Encoding"] == "chunked")
            return (true);
    }
    return (false);
}

void    HTTP_Request::printGetRequestLine(void) const
{
    std::cout << "[+] Method -> GET\n";
    std::cout << "[+] Path -> " << method.__get.__path << "\n";
    std::cout << "[+] Version -> " << method.__get.__version << "\n";
    if (method.__get.__query != "")
        std::cout << "[+] Query -> " << method.__get.__query << "\n";
    else
        std::cout << "[+] Query -> No Query\n";
    std::cout << "\n";
}

void   HTTP_Request::printPostRequestLine(void) const
{
    std::cout << "[+] Method -> POST\n";
    std::cout << "[+] Path -> " << method.__post.__path << "\n";
    std::cout << "[+] Version -> " << method.__post.__version << "\n";
    if (method.__post.__query != "")
        std::cout << "[+] Query -> " << method.__post.__query << "\n";
    else
        std::cout << "[+] Query -> No Query\n";
    std::cout << "\n";
}

void    HTTP_Request::printRequestLine(void) const
{
    if (methodType == _GET)
        printGetRequestLine();
    if (methodType == _POST)
        printPostRequestLine();
}

void    HTTP_Request::printGetHeaders(void) const
{
    std::map<std::string, std::string>::const_iterator it;
    for (it = method.__get.__headers.begin(); it != method.__get.__headers.end(); ++it)
        std::cout << "[.] " << it->first << " -> " << it->second << "\n";
    std::cout << "\n";
}

void    HTTP_Request::printPostHeaders(void) const
{
    std::map<std::string, std::string>::const_iterator it;
    for (it = method.__post.__headers.begin(); it != method.__post.__headers.end(); ++it)
        std::cout << "[.] " << it->first << " -> " << it->second << "\n";
    std::cout << "\n";
}

void    HTTP_Request::printHeaders(void) const
{
    if (methodType == _GET)
        printGetHeaders();
    if (methodType == _POST)
        printPostHeaders();
}

void    HTTP_Request::printBody(void) const
{
    if (methodType == _POST)
        std::cout << method.__post.__body << "\n";
    else
        std::cout << "No Body\n";
}

void    HTTP_Request::clearMembers(void)
{
    method.__get.__headers.clear();
    method.__post.__headers.clear();
    method.__get.__path.clear();
    method.__post.__path.clear();
    method.__get.__query.clear();
    method.__post.__query.clear();
    method.__get.__version.clear();
    method.__post.__version.clear();
    method.__post.__body.clear();
    request.clear();
    methodType = _NONE;
}