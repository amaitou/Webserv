#include "../../includes/HTTP_Respons.hpp"
#include "../../includes/CGI.hpp"

std::string Respons::getCurrentPath(void) {
    std::string locationPath;
    std::string root = _server.currentLocation().root();
    std::string file;
    size_t      idx;
    if (_server.currentLocation().alias().empty())
        locationPath = _server.currentLocation().path();
    else
        locationPath = _server.currentLocation().alias();

    if (!_request.getFileExtension().empty()) {
        idx = _request.getPath().find_last_of('/');
        if (idx != std::string::npos)
            file = _request.getPath().substr(idx);
    }
    if (locationPath.length() == 1 && locationPath[0] == '/')
        locationPath = "";

    return root + locationPath + file;
}

int Respons::checkResource(void) {
    std::string path = getCurrentPath();
    struct stat buffer;

    if (stat(path.c_str(), &buffer) != 0) {
        std::cout << path << '\n';
        // exit(1);

        setStatusCode(404);
        return 1;
    }

    return 0;
}

std::string Respons::getIndexPath(void) {
    std::string                 path    = getCurrentPath();
    std::vector<std::string>    indes   = _server.currentLocation().index();
    std::string                 index;
    struct stat                 buffer;

    for (size_t i = 0; i < indes.size(); i++) {
        index = path + "/" + indes[i];
        if (stat(index.c_str(), &buffer) == 0)
            return index;
    }
    return "";
}

void    Respons::servAutoIndex() {
    std::string         path = getCurrentPath();
    DIR                 *dir;
    struct dirent       *entry;
    std::stringstream   content;

    dir = opendir(path.c_str());
    if (!dir) {
        setStatusCode(404);
        return servErrorPage();
    }
    content << "<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Document</title></head><body>" << '\n';
    content << "<h3> <a href='" << _request.getPath() << "'>" << _request.getPath() << "</a></h3><ol>" << '\n';
    while ((entry = readdir(dir)) != NULL) {
        content << "<li><p><a href='" << entry->d_name << "'>" << entry->d_name << "</a></p></li>" << '\n';
    }
    content << "</ol></body></html>" << '\n';
    closedir(dir);
    sendResponsContent(content.str(), 200, "text/html");
}

Result    Respons::handleFolder() {
    std::string index;

    if (_request.getPath()[_request.getPath().length() - 1] != '/') {
        setStatusCode(301);
        sendRedirection(_request.getPath() + "/", 301);
        return Result(this->_responsContent);
    }

    index = getIndexPath();
    if (!index.empty())
        return handleFile(index);
    else if (_server.currentLocation().autoIndex() == "on") {
        servAutoIndex();
        return Result(this->_responsContent);
    }
    setStatusCode(403);
    servErrorPage();
    return Result(this->_responsContent);
}

Result    Respons::handleCgi(std::string path) {
    std::string allPath;

    if (path.empty())
        allPath = getCurrentPath();
    else 
        allPath = path;

    CgiHandler  cgi(_clientFd ,allPath, getMethodString(_request.getMethodType()), _request.getFileExtension(), _request.getBody());

    return Result(cgi.handleRequest());
}

std::string Respons::getExtentionOfFile(std::string path) {
    std::string extention;
    size_t      idx = path.find_last_of(".");

    idx++;
    if (idx != std::string::npos)
        extention = path.substr(idx, path.length() - idx);

    return extention;
}

Result    Respons::handleFile(std::string path) {
    if ((_request.getFileExtension() == "py" || getExtentionOfFile(path) == "py") && _server.currentLocation().cgi() == "on")
        return handleCgi(path);
    else  if ((_request.getFileExtension() == "php" || getExtentionOfFile(path) == "php") && _server.currentLocation().cgi() == "on")
        return handleCgi(path);
    else  if ((_request.getFileExtension() == "bash" || getExtentionOfFile(path) == "bash") && _server.currentLocation().cgi() == "on")
        return handleCgi(path); 

    std::ifstream                                   file(path);
    std::string                                     content;
    std::map<std::string, std::string>              mimeType = _server.mimeType();
    std::map<std::string, std::string>::iterator    it       = mimeType.begin();

    if (!file.is_open()) {
        setStatusCode(404);
        servErrorPage();
        return Result(this->_responsContent);
    }
    setStatusCode(200);
    content.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    for(; it != mimeType.end(); it++) {
        if (it->first.find(_request.getFileExtension()) != std::string::npos) {
            sendResponsContent(content, getStatusCode(), it->second);
            return Result(this->_responsContent);
        }
    }
    sendResponsContent(content, getStatusCode(), "text/plain");
    return Result(this->_responsContent);
}

Result    Respons::servGet(void) {
    if (checkResource()) {
        servErrorPage();
        return Result(this->_responsContent);
    }
    if (_request.getFileExtension().empty()) {
        handleFolder();
        return Result(this->_responsContent);
    }

    return handleFile(getCurrentPath());
}
