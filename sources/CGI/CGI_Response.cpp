#include "../../includes/CGI_Response.hpp"

void setNonBlocking(int fd) {
    if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0)
		throw std::invalid_argument("can't set fd to non blocking mode");
}

CGI_Response::CGI_Response(int client, int pid, int writefd, int readfd, std::string _input) : 
    input(_input),
    pid(pid),
    fd_client(client),
    fd_write(writefd),
    fd_read(readfd)
{
    // std::cout << "new cgi response " << fd_client << " " << pid << " " << fd_write << " " << fd_read << std::endl;
    setNonBlocking(fd_write);
    setNonBlocking(fd_read);

    done = false;
}

CGI_Response::~CGI_Response() {
    int r = ::waitpid(pid, NULL, WNOHANG);
    if (r == -1) {
        ::kill(pid, SIGKILL);
        ::waitpid(pid, NULL, WNOHANG);
    }
    close(fd_read);
    close(fd_write);
}

bool CGI_Response::is_done() {
    return done;
}


bool CGI_Response::readCgi() {
    // std::cout << "reading from cgi " << fd_read << std::endl;
    char buffer[4096];
    int bytesRead = read(fd_read, buffer, sizeof(buffer));
    if (bytesRead == -1) {
        perror("read error: ");
        std::string body = "<h1 style='text-align:center;'>500 Server Error</h1>";
        output = "status: 500 Server Error\r\nContent-Type: text/html\r\nContent-Length: " + std::to_string(body.length());
        output += "\r\n\r\n" + body;
        return true;
    }
    // std::cout << bytesRead << std::endl;
    if (bytesRead > 0)
        output += std::string(buffer, bytesRead);
    
    // std::cout << output << std::endl;

    if (bytesRead == 0)
        return true;
    return false;
}

void CGI_Response::writeCgi() {
    if (input.empty())
        return ;
    
    int r = ::write(fd_write, input.data(), input.length());
    if (r > 0)
        input.erase(0, r);
}

std::string CGI_Response::getResponsContent() {

    done = true;

    size_t end_header_pos = output.find("\r\n\r\n");
    if (end_header_pos == std::string::npos)
        end_header_pos = output.find("\n\n");
    // if (end_header_pos == npos) 
        // return serverError(502);
        
    std::string header = output.substr(0, end_header_pos);
    // int err = parseHeader(header)
    // if (err || !checkHeaderValidity())
    //     return serverError(502);
    std::map<std::string, std::string>::iterator it = headers.find("status");
    if (it != headers.end()) {
        std::string status = it->second;
        if (status[status.length() - 1] == '\r') status.pop_back();
        headers.erase(it);
        std::string newHeader = "HTTP/1.1 " + status + "\r\n"; // HTTP/1.1 201 Created
        output.erase(0, end_header_pos + 2);
        for (it = headers.begin(); it != headers.end(); ++it)
            newHeader += it->first + ": " + it->second + "\r\n";
        output = newHeader + output;
    }
    else 
        output = "HTTP/1.1 200 Ok\r\nConnection: close\r\n" + output;

    // std::cout << "out: " << output << std::endl;
    
    return output;
}

