/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTP_Request.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 05:40:58 by amait-ou          #+#    #+#             */
/*   Updated: 2024/01/21 20:44:23 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <string>
#include <cstring>
#include <sstream>
#include <iostream>
#include <map>

// Method Enum
typedef enum _e_method
{
    _GET,
    _POST,
    _DELETE,
    _NONE
} e_method;

// GET Structure
typedef struct _s_get
{
    std::string __path;
    std::string __version;
    std::string __query;
    std::map<std::string, std::string> __headers;
} s_get;

// POST Structure

typedef struct _s_post
{
    std::string __path;
    std::string __version;
    std::string __query;
    std::string __body;
    std::map<std::string, std::string> __headers;
} s_post;

// Method Structure

typedef struct _s_method
{
    s_get __get;
    s_post __post;
} s_method;

// HTTP Request Class
class HTTP_Request
{
    private:
        s_method method;
        e_method methodType;
        std::string request;
    
    public:

        // Constructors
        HTTP_Request();
        HTTP_Request(char *request);

        // Getters
        e_method getMethodType(void) const;
        
        std::string getGetPath(void) const;
        std::string getGetVersion(void) const;
        std::string getGetQuery(void) const;
        std::map<std::string, std::string> getGetHeaders(void) const;

        std::string getPostPath(void) const;
        std::string getPostVersion(void) const;
        std::string getPostQuery(void) const;
        std::string getPostBody(void) const;
        std::map<std::string, std::string> getPostHeaders(void) const;

        // Setters
        void    setRequest(char *s);

        // Parser
        void    parseRequest(void);
        void    parseGet(std::string &__temp_path, std::stringstream &stream, std::string &__request_line);
        void    parsePost(std::string &__temp_path, std::stringstream &stream, std::string &__request_line);
        void    parsePostChunkedData(std::stringstream &stream, std::string &__request_line);
        bool    checkChunkedData(void);

        // Get Printers
        void    printGetRequestLine(void) const;
        void    printGetHeaders(void) const;

        void    printPostRequestLine(void) const;
        void    printPostHeaders(void) const;

        void    printRequestLine(void) const;
        void    printHeaders(void) const;
        void    printBody(void) const;


        // Cleaners
        void clearMembers(void);
};

#endif