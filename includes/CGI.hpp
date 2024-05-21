/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 11:40:26 by ael-amin          #+#    #+#             */
/*   Updated: 2024/05/21 13:21:05 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
#define CGI_HPP

#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <vector>
#include <sstream>
#include <map>


class CgiHandler
{
    private:
        std::string cgiPath;
        std::string requestMethod;
        std::string cgiExtention;
        std::string responseBody;
        std::string requestBody;
        int         statusCode;

        void executeCgi();

    public:
        CgiHandler(std::string , std::string , std::string , std::string );
        ~CgiHandler();
        
        int             getStatusCode() const;
        std::string     getResponseBody() const;
        void            handleRequest();
        bool            readCgi(int, char *, std::string &);
        void            writeCgi(int, std::string &);
        std::string     getResponsContent(std::string &);
};

#endif
