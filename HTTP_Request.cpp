/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTP_Request.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 05:40:53 by amait-ou          #+#    #+#             */
/*   Updated: 2024/01/18 05:40:54 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

std::string HTTP_Request::getQuery(void) const
{
    return (method.__query);
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
            method.__path = __temp_path;
        while (std::getline(stream, __request_line))
        {
            std::string _key;
            std::string _value;
            if (__request_line == "\r\n")
                continue;
            size_t position = __request_line.find(":");
            _key = __request_line.substr(0, position);
            _value = __request_line.substr(position + 2, __request_line.length());
            method.__headers.insert(std::make_pair(_key, _value));
        }
    }
    else if (__method == "POST")
        method.__method = _POST;
    else if (__method == "DELETE")
        method.__method = _DELETE;
    else
        method.__method = _NONE;
}