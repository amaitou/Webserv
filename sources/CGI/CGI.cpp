/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:09:55 by ael-amin          #+#    #+#             */
/*   Updated: 2024/05/21 10:23:21 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/CGI.hpp"


CgiHandler::CgiHandler(std::string _path, std::string _method, std::string _extention, std::string _body) {
    this->cgiPath = _path;
    this->requestMethod = _method;
    this->cgiExtention = _extention;
    this->requestBody = _body;
    this->statusCode = 200;
}

CgiHandler::~CgiHandler() {}

std::string CgiHandler::getResponseBody() const { return responseBody; }
int         CgiHandler::getStatusCode() const { return statusCode; }

void CgiHandler::executeCgi() {
    int pipeIn[2];
    int pipeOut[2];
    pid_t pid;
    char buffer[4096];
    int status;

    if (pipe(pipeIn) == -1 || pipe(pipeOut) == -1) {
        statusCode = 500;
        return;
    }

    pid = fork();
    if (pid == -1) {
        statusCode = 500;
        return;
    }
    if (pid == 0) {
        close(pipeIn[1]);
        close(pipeOut[0]);
        dup2(pipeIn[0], 0);
        close(pipeIn[0]);
        dup2(pipeOut[1], 1);
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
    } else {
        close(pipeIn[0]);
        close(pipeOut[1]);
        write(pipeIn[1], requestBody.c_str(), requestBody.size());
        close(pipeIn[1]);

        std::string output;
        ssize_t bytesRead;
        while ((bytesRead = read(pipeOut[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytesRead] = '\0';
            output += buffer;
        }
        close(pipeOut[0]);

        waitpid(pid, &status, 0);

        responseBody = output;
    }
}

void CgiHandler::handleRequest() {

    executeCgi();
}
