/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:09:55 by ael-amin          #+#    #+#             */
/*   Updated: 2024/05/21 14:40:13 by rlabbiz          ###   ########.fr       */
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

        /*
            pipe1 (to send to cgi)
            pipe2 (to read from cgi)

            child:
                close(pipe1[1])
                close(pipe2[0])
                execve()

            parent:
                close(pipe1[0])
                close(pipe2[1])

                close(pipe1[1]) -> setNonBlocking()
                close(pipe2[0]) -> setNonBlocking()
                
                {
                    fd_client -> public const
                    fd_write -> public const
                    fd_read -> public const
                    [buffer_write]<-input
                    [buffer_read]<-output

                    headers [map]

                    read()
                    write()
                    getResponseContent()
                }
                


                bool read() {
                    ssize_t bytesRead = read(pipeOut[0], buffer, sizeof(buffer));
                    output += std::string(buffer, bytesRead)
                    if (bytesRead == 0)
                        return true;
                    return false;
                }

                void write() {
                    if (input.empty()) return;
                    
                    int r = ::write(pipeIn[1]/fd_write, input.data(), input.length());
                    if (r > 0) input.erase(0, r);
                }
                
                string getResponseContent() {
                    size_t end_header_pos = output.find("\r\n\r\n");
                    if (end_header_pos == npos)
                        end_header_pos = output.find("\n\n");


                    if (end_header_pos == npos) 
                        return serverError(502);
                        
                    string header = output.substr(0, end_header_pos);
                    int err = parseHeader(header)

                    if (err || !checkHeaderValidity())
                        return serverError(502);

                    string_string_map::iterator it = headers.find("status");
                    if (it != headers.end()) {
                        string status = it->second;
                        if (status[status.length() - 1] == '\r') status.pop_back();
                        headers.erase(it);
                        string newHeader = "HTTP/1.1 " + status + "\r\n"; // HTTP/1.1 201 Created

                        output.erase(0, end_header_pos + 2);

                        for (it = headers.begin(); it != headers.end(); ++it)
                            newHeader += it->first + ": " + it->second + "\r\n";

                        output = newHeader + output;

                    }
                    else 
                        output = "HTTP/1.1 200 Ok\r\nConnection: close\r\n" + output;
                    
                    return output;
                }

                void    parseHeader(){}



                // lelouch
                if (cgi->read())
                {
                    int fd = cgi->getClientFd();
                    clients[fd].respons.sendRespons(clients[fd], this->clients[fd].config);
		            this->clients[fd].responseContent = clients[fd].respons.getResponsContent();
                }

                fd_client -> public const
                fd_write -> public const
                fd_read -> public const
                [buffer_write]<-input
                [buffer_read]<-output

                return (CGI_Response(fd_client, pipeIn[1], pipeOut[0], input))

                class CGI_Response {
                    
                    std::string output;
                    std::string input;
                    
                    public:
                        const int fd_client;
                        const int fd_write;
                        const int fd_read;
                }

                // Lelouch
                map clients

                mux -> fd_write/fd_read
                map cgi

                // cgi response
                CGI_Response r = client[fd].cgi_response
                FD_SET(r.fd_write)
                FD_SET(r.fd_read)

                // write
                for c in cgis:
                    if (c->fd_write == mx_fd_write)
                        c->write
                // read
                for (c in cgis) {
                    if (c->fd_read == mx_fd_read) {
                        if (cgi->read())
                        {
                            int fd = cgi->getClientFd();
                            clients[fd].respons.sendRespons(clients[fd], this->clients[fd].config);
                            this->clients[fd].responseContent = clients[fd].respons.getResponsContent();
                        }
                    }
                }
                
        */

        std::string output;
        ssize_t bytesRead;
        while ((bytesRead = read(pipeOut[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytesRead] = '\0';
            output += buffer;
            // output += std::string(buffer, bytesRead)
        }
        
        close(pipeOut[0]);

        waitpid(pid, &status, 0);

        responseBody = output;
    }
}

void CgiHandler::handleRequest() {
    executeCgi();
}
