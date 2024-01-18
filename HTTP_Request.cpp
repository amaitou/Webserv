/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTP_Request.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 05:40:53 by amait-ou          #+#    #+#             */
/*   Updated: 2024/01/18 07:25:44 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HTTP_Request.hpp"

HTTP_Request::HTTP_Request() {}

HTTP_Request::HTTP_Request(char *request)
{
    memset((char *)&method, 0, sizeof(method));
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

std::string HTTP_Request::getQuery(void) const
{
    return (method.__query);
}

e_method HTTP_Request::getMethod(void) const
{
    return (method.__method);
}

std::map<std::string, std::string> HTTP_Request::getHeaders(void) const
{
    return (method.__headers);
}

void    HTTP_Request::setRequest(char *request)
{
    this->request = std::string(request);
}

void    HTTP_Request::printRequestLine(void) const
{
    std::cout << "[*] Path -> " << method.__path << "\n";
    std::cout << "[*] Version -> " << method.__version << "\n";
    if (method.__query != "")
        std::cout << "[*] Query -> " << method.__query << "\n";
    else
        std::cout << "[*] Query -> NONE\n";
    if (method.__method == _GET)
        std::cout << "[*] Method -> GET\n";
    else if (method.__method == _POST)
        std::cout << "[*] Method -> POST\n";
    else if (method.__method == _DELETE)
        std::cout << "[*] Method -> DELETE\n";
    else
        std::cout << "[*] Method -> NONE\n";
    std::cout << "\n";
}

void    HTTP_Request::printHeaders(void) const
{
    std::map<std::string, std::string>::const_iterator it;
    for (it = method.__headers.begin(); it != method.__headers.end(); ++it)
        std::cout << "[.] " << it->first << " -> " << it->second << "\n";
    std::cout << "\n";
}


void    HTTP_Request::parseRequest(void)
{
    std::string __method;
    std::string __request_line;
    std::string __temp_path;

    std::stringstream stream(request);
    std::getline(stream, __request_line);
    std::stringstream __temp(__request_line);
    __temp >> __method >> __temp_path >> method.__version;
    if (__method == "GET")
    {
        method.__method = _GET;
        if (__temp_path.find("?") != std::string::npos)
        {
            size_t position = __temp_path.find("?");
            method.__path = __temp_path.substr(0, position);
            method.__query = __temp_path.substr(position + 1, __temp_path.length());
        }
        else
        {
            method.__path = __temp_path;
            method.__query = "";
        }
        while (std::getline(stream, __request_line))
        {
            std::string _key;
            std::string _value;
            if (__request_line == "\r")
                continue;
            size_t position = __request_line.find(":");
            _key = __request_line.substr(0, position);
            _value = __request_line.substr(position + 2, __request_line.length());
            method.__headers.insert(std::make_pair(_key, _value));
        }
        method.__body = "";
    }
    else if (__method == "POST")
        method.__method = _POST;
    else if (__method == "DELETE")
        method.__method = _DELETE;
    else
        method.__method = _NONE;
}