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
    write_done = false;
}

CGI_Response::~CGI_Response() {
    int r = ::waitpid(pid, NULL, WNOHANG);
    if (r == -1) {
        ::kill(pid, SIGKILL);
        ::waitpid(pid, NULL, WNOHANG);
    }
    close(fd_read);
    if (!write_done)
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

    std::cout << output << std::endl;

    if (bytesRead == 0)
        return true;
    return false;
}

bool CGI_Response::writeCgi() {
    if (input.empty())
        return false;

    int r = ::write(fd_write, input.data(), input.length());
    if (r > 0)
        input.erase(0, r);
    return false;
}

std::string CGI_Response::serverError(int code)
{
    return "HTTP/1.1 " + std::to_string(code) + " Bad Gateway\r\nConnection: close\r\n\r\n<h1>" + std::to_string(code) + "</h1>\r\n\r\n";
}

bool CGI_Response::isValidStatusCode(const std::string& status)
{
    return(status.size() >= 3 && isdigit(status[0]) && isdigit(status[1] && isdigit(status[2])));
}

bool CGI_Response::isValidContentLength(const std::string& contentlength)
{
    for (size_t i = 0; i < contentlength.size(); ++i)
    {
        if(!isdigit(contentlength[i]))
        {
            return false;
        }
    }
    return true;
}

bool CGI_Response::checkHeaderValidity(const std::map<std::string, std::string>& headers)
{
    std::map<std::string, std::string>::const_iterator it = headers.find("Content-Type");
    if(it == headers.end())
    {
        std::cerr << "Error: Missing Content-Type header" << std::endl;
        return false;
    }

    it = headers.find("Status");
    if (it != headers.end() && !isValidStatusCode(it->second))
    {
        std::cerr << "Error: Invalid Status header" << std::endl;
        return false;
    }

    it = headers.find("Content-Length");
    if(it != headers.end() && !isValidContentLength(it->second))
    {
        std::cerr << "Error: Invalid Content-Length header" << std::endl;
        return false;
    }
    return true;
}

int CGI_Response::parseHeader(const std::string &header, std::map<std::string, std::string>& headers)
{
	std::istringstream headerStream(header);

	std::string line;

	while(std::getline(headerStream, line) && !line.empty())
	{
		size_t pos = line.find(':');
		if (pos != std::string::npos)
		{
			std::string key = line.substr(0, pos);
			std::string value = line.substr(pos + 1);
            headers[key] = value;
		}
	}
    return 0;
}

std::string CGI_Response::getResponsContent() {

    done = true;

    size_t end_header_pos = output.find("\r\n\r\n");
    if (end_header_pos == std::string::npos)
        end_header_pos = output.find("\n\n");
    if (end_header_pos == std::string::npos)
        return serverError(502);

    std::string header = output.substr(0, end_header_pos);
    int err = parseHeader(header, headers);
    if (err || !checkHeaderValidity(headers))
        return serverError(502);
    std::map<std::string, std::string>::iterator it = headers.find("status");
    if (it != headers.end()) {
        std::string status = it->second;
        if (status[status.length() - 1] == '\r') status.pop_back();
        headers.erase(it);
        std::string newHeader = "HTTP/1.1 " + status + "\r\n";
        output.erase(0, end_header_pos + 2);
        for (it = headers.begin(); it != headers.end(); ++it)
            newHeader += it->first + ": " + it->second + "\r\n";
        output = newHeader + output;
    }
    else
        output = "HTTP/1.1 200 Ok\r\nConnection: close\r\n" + output;

    std::cout << "out: " << output << std::endl;

    return output;
}
