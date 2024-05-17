/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI_Handler.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-amin <ael-amin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 11:40:26 by ael-amin          #+#    #+#             */
/*   Updated: 2024/05/16 13:22:30 by ael-amin         ###   ########.fr       */
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


class CgiHandler {
private:
    std::string cgiPath;
    std::string responseBody;
    std::string requestBody;

    void executeCgi(const std::string& scriptPath, const std::string& requestMethod, const std::string& requestBody);

public:
    CgiHandler(const std::string& cgiPath);
    ~CgiHandler();

    std::string   getResponseBody() const;
    void handleRequest(const std::string& method, const std::string& url, const std::string& body);
};

#endif
