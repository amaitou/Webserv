#include "../../includes/Parser.hpp"
#include "../../includes/HTTP_Request.hpp"
#include "../../includes/HTTP_Respons.hpp"
#include "../../includes/Client_Instance.hpp"

Respons::Respons() {}
Respons::~Respons() {}

std::string Respons::getIp(std::string str) {
    size_t idx = str.find(':');

    if (idx != std::string::npos) {
        return str.substr(0, idx);
    } else 
        return str;
}

int Respons::getPort(std::string str) {
    size_t idx = str.find(':');

    if (idx != std::string::npos) {
        idx++;
        if (idx == str.length())
            return 8080;
        return std::atoi(str.substr(idx, str.length() - idx).c_str());
    } else 
        return 8080;
}

int Respons::foundCurrentServer(HTTP_Request http, Config config) {
    std::map<std::string, std::string>              headers = http.getHeaders();
    std::map<std::string, std::string>::iterator    it      = headers.begin();
    std::string                                     ip;
    int                                             port = config.listen()[0];

    for (; it != headers.end(); it++) {
        if (it->first == "Host") {
            ip      = getIp(it->second);
            port    = getPort(it->second);
            break ;
        }
    }

    setStatusCode(200);
    _server = config;
    setCurrentPort(port);
    return 0;
}

std::string Respons::generateErrorPage(int statusCode) {
    std::stringstream content;

    content << "<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'>" << '\n';
    content << "<script src='ttps://kit.fontawesome.com/8c404414cb.js' crossorigin='anonymous'></script><link rel='stylesheet' href='style.css'><title>" << statusCode << " - " << getStatusCodeString(statusCode) << "</title>" << '\n';
    content << "<style>" << '\n';
    content << "@import url('https://fonts.googleapis.com/css2?family=Tajawal:wght@200;300;400;500;700;800;900&display=swap');" << '\n';
    content << "* {padding: 0;margin: 0;box-sizing: border-box;font-family: 'Tajawal', sans-serif;}body {background-color: #0000000f;}a {text-decoration: none;}.container {width: 2000px;height: auto;margin: 400px auto;text-align: center;overflow: hidden;border-radius: 5px;}" << '\n';
    content << ".container .title {width: 100%;margin-bottom: 50px;}.container .title h1 {color: green;font-size: 300%;}.client, .server {width: 50%;margin: 50px 0;}.client {float: left;border-right: 1px solid #00000030;}.server {float: right;}.client h2, .server h2 {color: #9e9e9e;margin-bottom: 20px;font-size: 200\%;}" << '\n';
    content << ".client div, .server div {margin-top: 20px;}.client div a, .server div a {font-size: 115\%;}.badRequest {width: 800px;height: auto;margin: 300px auto;text-align: center;}.badRequest i.logo {font-size: 1200\%;color: #0000007d;margin-bottom: 15px;}.badRequest h1 {font-size: 600\%;color: #0000007d;}.badRequest h3 {font-size: 200\%;color: #00000030;margin-bottom: 15px;}" << '\n';
    content << ".badRequest p {font-size: 150\%;color: #00000030;margin-bottom: 15px;}.links {width: 100\%;border-top: 1px solid #00000030;padding-top: 20px;margin-top: 50px;display: flex;justify-content: space-evenly;}.badRequest a {margin-bottom: 15px;display: block;color: #0000007d;}.links h4 {color: #00000030;font-size: 120\%;margin-left: 28px;}" << '\n';
    content << "</style>" << '\n';
    content << "</head><body><div class='badRequest'><i class='far fa-meh logo'></i><h1>" << statusCode << "</h1><h3>" << getStatusCodeString(statusCode) << "</h3>" << '\n';
    content << "<p>" << getStatusCodeDescription(statusCode) << "</p><div class='links'><a href='index.html' class='left'><i class='fas fa-arrow-left'></i> Go Back</a>" << '\n';
    content << "<h4>Weserv</h4><a href='index.html' class='right'>Go To Home Page <i class='fas fa-arrow-right'></i></a></div></div></body></html>" << '\n';

    return content.str();
}

std::string Respons::getStatusCodeString(int statusCode) {
    switch (statusCode) {
        case 200:
            return "OK";
        case 201:
            return "Created";
        case 204:
            return "No Content";
        case 301:
            return "Moved Permanently";
        case 400:
            return "Bad Request";
        case 403:
            return "Forbidden";
        case 404:
            return "Not Found";
        case 405:
            return "Method Not Allowed";
        case 413:
            return "Payload Too Large";
        case 500:
            return "Internal Server Error";
        case 501:
            return "Not Implemented";
        default:
            return "Not Found";
    }
}

std::string Respons::getStatusCodeDescription(int statusCode) {
    switch (statusCode) {
        case 201:
            return "The request has been fulfilled and has resulted in one or more new resources being created.";
        case 204:
            return "The server has successfully fulfilled the request and that there is no additional content to send in the response payload body.";
        case 301:
            return "The URL of the requested resource has been changed permanently.";
        case 400:
            return "The server cannot or will not process the request due to an apparent client error.";
        case 403:
            return "The server understood the request but refuses to authorize it.";
        case 404:
            return "The server has not found anything matching the Request-URI.";
        case 405:
            return "The method specified in the Request-Line is not allowed for the resource identified by the Request-URI.";
        case 413:
            return "The server is refusing to process a request because the request entity is larger than the server is willing or able to process.";
        case 500:
            return "The server encountered an unexpected condition that prevented it from fulfilling the request.";
        case 501:
            return "The server does not support the functionality required to fulfill the request.";
        default:
            return "The request has succeeded.";
    }
}

void    Respons::servErrorPage(void) {
    int                                             errorNum    = getStatusCode();
    std::map<std::string, std::string>              errorPages  = _server.currentLocation().errorPage();
    std::map<std::string, std::string>::iterator    it          = errorPages.begin();
    struct stat                                     buffer;
    std::string                                     path;
    std::string                                     filePath;

    for (; it != errorPages.end(); it++) {
        if (std::atoi(it->first.c_str()) == errorNum) {
            path = getCurrentPath();
            if (path.find_last_of(".") != std::string::npos)
                path = path.substr(0, path.find_last_of("/")) + "/" + it->second;
            else
                path = path + "/" + it->second;
            if(stat(path.c_str(), &buffer) == 0) {
                if (_server.currentLocation().path() == "/")
                    filePath = _server.currentLocation().path() + it->second;
                else 
                    filePath = _server.currentLocation().path() + "/" + it->second;
                return sendRedirection(filePath, 301);
            }
            break ;
        }
    }

    sendResponsContent(getClientFd(), generateErrorPage(getStatusCode()), getStatusCode(), "text/html");
}

void    Respons::sendResponsContent(int fd, std::string content, int statusCode, std::string plain) {
    std::string allContent = "HTTP/1.1 " + std::to_string(statusCode) + " " + "OK" + " Content-Type: " + plain + "\nContent-Length:" + std::to_string(content.length()) + "\n\n" + content + "\n"; 
    write(fd, allContent.c_str(), allContent.length());
}

void    Respons::sendRedirection(std::string url, int statusCode) {
    std::string allContent = "HTTP/1.1 " + std::to_string(statusCode) + " Moved Permanently\r\nLocation: " + url + "\r\n\r\n";
    write(getClientFd(), allContent.c_str(), allContent.length());
}

void    Respons::sendRespons(Client  & client, Config config) {
    setClientFd(client.getClientFd());
    _request = client.request;

    foundCurrentServer(client.request, config);

    if (checkValidUrl(client.request.getPath() + "?" + client.request.getQuery())) {
        servErrorPage();
        return ;
    }


    if (_server.currentLocation().redirection().size() != 0) {
        std::map<std::string, int> redirection = _server.currentLocation().redirection();
        sendRedirection(redirection.begin()->first, redirection.begin()->second);
        setStatusCode(301);
        return ;
    }

    if (_request.getMethodType() == GET) 
        return servGet();
    if (_request.getMethodType() == POST) 
        return servPost();
    if (_request.getMethodType() == DELETE) 
        return servDelete();

    sendResponsContent(getClientFd(), "correct", getStatusCode(), "text/plain");
}
