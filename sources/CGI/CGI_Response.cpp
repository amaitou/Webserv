#include "../../includes/CGI_Response.hpp"

CGI_Response::CGI_Response(int client, int writefd, int readfd, std::string _input) : fd_client(client), fd_write(writefd), fd_read(readfd) {
    this->input = _input;
}

CGI_Response::~CGI_Response() {}


bool CGI_Response::readCgi(int out, char buffer[4096], std::string & outPut) {
    size_t bytesRead = read(out, buffer, sizeof(buffer));
    outPut += std::string(buffer, bytesRead);
    if (bytesRead == 0)
        return true;
    return false;
}

void CGI_Response::writeCgi(int in, std::string & input) {
    if (input.empty())
        return ;
    
    int r = ::write(in, input.data(), input.length());
    if (r > 0)
        input.erase(0, r);
}

std::string CGI_Response::getResponsContent(std::string & output) {
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
    
    return output;
}

