#pragma once

#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <vector>
#include <sstream>
#include <signal.h>

#include <map>


class CGI_Response {
    private:
        std::string output;
        std::string input;
        int         pid;
        std::map<std::string, std::string> headers;
        bool        done;

    public:
        CGI_Response(int fd_client, int cgi_pid, int fd_read, int fd_write, std::string input);
        ~CGI_Response();

        bool            readCgi();
        void            writeCgi();
        std::string     getResponsContent();
        bool            is_done();


    public:
        const int   fd_client;
        const int   fd_write;
        const int   fd_read;
};
