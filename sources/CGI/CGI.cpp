/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:09:55 by ael-amin          #+#    #+#             */
/*   Updated: 2024/05/21 18:39:11 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/CGI.hpp"


CgiHandler::CgiHandler(int fd_client, std::string _path, std::string _method, std::string _extention, std::string _body) {
    this->fd_client = fd_client;
    this->cgiPath = _path;
    this->requestMethod = _method;
    this->cgiExtention = _extention;
    this->requestBody = _body;
    this->statusCode = 200;
}

CgiHandler::~CgiHandler() {}

std::string CgiHandler::getResponseBody() const { return responseBody; }
int         CgiHandler::getStatusCode() const { return statusCode; }

CGI_Response* CgiHandler::handleRequest() {
    int pipeIn[2];
    int pipeOut[2];
    pid_t pid;

    if (pipe(pipeIn) == -1 || pipe(pipeOut) == -1) {
        statusCode = 500;
        return NULL;
    }

    // std::cout << "pipe read: " << pipeIn[0] << ' ' << pipeOut[0] << std::endl;
    // std::cout << "pipe write: " << pipeIn[1] << ' ' << pipeOut[1] << std::endl;

    pid = fork();
    if (pid == -1) {
        statusCode = 500;
        return NULL;
    }
    if (pid == 0) {
        close(pipeIn[1]);
        close(pipeOut[0]);

        dup2(pipeIn[0], 0);
        dup2(pipeOut[1], 1);
        
        close(pipeIn[0]);
        close(pipeOut[1]);

        std::vector<const char*> args;
        if (cgiExtention == "py")
            args.push_back("/usr/bin/python3");
        else if (cgiExtention == "php")
            args.push_back("/usr/bin/php");
        else if (cgiExtention == "bash")
            args.push_back("/bin/bash");
        args.push_back(cgiPath.c_str());
        args.push_back(NULL);

        std::vector<const char*> env;
        env.push_back("GATEWAY_INTERFACE=CGI/1.1");
        env.push_back(("REQUEST_METHOD=" + requestMethod).c_str());
        env.push_back(("SCRIPT_NAME=" + cgiPath).c_str());
        env.push_back(NULL);

        execve(args[0], (char* const*)args.data(), (char* const*)env.data());
        statusCode = 405;
        std::cerr << "Error: execve failed" << std::endl;
        std::exit(1);
    }
    
    close(pipeIn[0]);
    close(pipeOut[1]);
    
    // std::cout << "closed: " << pipeIn[0] << " " << pipeOut[1] << std::endl;

    // std::cout << "returning cgi_response" << std::endl;
    return new CGI_Response(fd_client, pid, pipeIn[1], pipeOut[0], requestBody);
}

