#include "../../includes/Respons.hpp"

int Respons::checkTransferEncoding(void) {
    std::map<std::string, std::string>              headers = _request.getHeaders();    
    std::map<std::string, std::string>::iterator    it      = headers.begin();
    for (; it != headers.end(); it++) {
        if (it->first == "Transfer-Encoding") {
            if (it->second != "chunked") {
                setStatusCode(501);
                return 1;
            }
            return 0;
        }
    }

    for (it = headers.begin(); it != headers.end(); it++) {
        if (it->first == "Content-Length")
            return 0;
    }

    if (_request.getMethodType() == POST) {
        setStatusCode(400);
        return 1;
    }
    return 0;
}

int Respons::checkUrl(std::string path) {
    std::string allowedCharacters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~:/?#[]@!$&'()*+,;=%";
    size_t      idx;
    
    for (size_t i = 0; i < path.length(); i++) {
        idx = allowedCharacters.find(path[i]);
        if (idx == std::string::npos) {
            setStatusCode(400);
            return 1;
        }
    }

    if (path.length() > 2048) {
        setStatusCode(414);
        return 1;
    }

    if (_request.getBody().length() > _server.bodySize()) {
        setStatusCode(413);
        return 1;
    }

    return 0;
}

int Respons::handleLocations() {
    std::vector<Location>   locations = _server.location();
    std::string             path = _request.getPath();
    size_t                  idx;

    if (_request.getFileExtension().empty()) {
        if (path.length() > 1 && path.at(path.length() - 1) == '/') 
            path.erase(--path.end());
    } else {
        idx = path.find_last_of('/');
        if (idx != std::string::npos && path.length() > 1)
            path = path.substr(0, idx);
    }

    if (path.empty())
        path = "/";

    for (size_t i = 0; i < locations.size(); i++) {
        if (path == locations[i].path()) {
            _server.setCurrentLocation(locations[i]);
            return 0;
        }
    }
    if (path == "/")
        return 0;
    
    setStatusCode(404);
    return 1;
}

std::string Respons::getMethodString(t_method_type method) {
    switch (method) {
        case GET:
            return "GET";
        case POST:
            return "POST";
        case DELETE:
            return "DELETE";
        default:
            return "NONE";
    }
}

int Respons::checkLocationMethod() {
    std::vector<std::string>    methods = _server.currentLocation().method();
    std::string                 method  = getMethodString(_request.getMethodType());

    for (size_t i = 0; i < methods.size(); i++) {
        if (methods[i] == method)
            return 0;
    }

    setStatusCode(405);
    return 1;
}

int Respons::checkValidUrl(std::string path) {
    if (checkTransferEncoding())
        return 1;

    if (checkUrl(path))
        return 1;

    if (handleLocations())
        return 1;

    if (checkLocationMethod())
        return 1;
    return 0;
}