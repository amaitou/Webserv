/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommonGatewayInterface.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 11:40:26 by ael-amin          #+#    #+#             */
/*   Updated: 2024/05/17 20:12:20 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_Handler_HPP
#define CGI_Handler_HPP

#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <vector>
#include <sstream>


class CgiHandler
{
    private:
        std::string cgiPath;
        std::string responseBody;
        std::string requestBody;

        void executeCgi(const std::string &, const std::string &, const std::string &);

    public:
        CgiHandler(const std::string &);
        ~CgiHandler();

        std::string     getResponseBody() const;
        void            handleRequest(const std::string &, const std::string &, const std::string &);
};

#endif
