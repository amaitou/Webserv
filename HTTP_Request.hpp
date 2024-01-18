/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTP_Request.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 05:40:58 by amait-ou          #+#    #+#             */
/*   Updated: 2024/01/18 08:21:54 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <string>
#include <cstring>
#include <sstream>
#include <iostream>
#include <map>

typedef enum _e_method
{
    _GET,
    _POST,
    _DELETE,
    _NONE
} e_method;

typedef struct _s_method
{
    std::string __path;
    std::string __version;
    std::string __query;
    std::string __body;
    e_method __method;
    std::map<std::string, std::string> __headers;
} s_method;

class HTTP_Request
{
    private:
        s_method method;
        std::string request;
    
    public:
        HTTP_Request();
        HTTP_Request(char *request);

        // Getters
        std::string getPath(void) const;
        std::string getVersion(void) const;
        std::string getQuery(void) const;
        e_method getMethod(void) const;
        std::map<std::string, std::string> getHeaders(void) const;

        // Setters
        void    setRequest(char *s);

        // Printers
        void    printHeaders(void) const;
        void    printRequestLine(void) const;

        // Parser
        void    parseRequest(void);
        void    parseGet(std::string &__temp_path, std::stringstream &stream, std::string &__request_line);
};

#endif