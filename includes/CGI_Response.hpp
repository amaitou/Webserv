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
        std::map<std::string, std::string> headers;

    public:
        CGI_Response(int , int , int , std::string );
        ~CGI_Response();

        bool            readCgi(int, char *, std::string &);
        void            writeCgi(int, std::string &);
        std::string     getResponsContent(std::string &);


    public:
        const int   fd_client;
        const int   fd_write;
        const int   fd_read;
};
