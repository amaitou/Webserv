#include "../../includes/HTTP_Respons.hpp"

int Respons::locationSupportUpload(void) {
    std::map<std::string, std::string> headers = _request.getHeaders();
    std::map<std::string, std::string>::iterator it = headers.begin();

    for (; it != headers.end(); it++) {
        if (it->first == "Content-Type" && it->second.find("multipart/form-data") != std::string::npos) {
            return 1;
        }
    }

    return 0;
}

std::string Respons::getFileName(std::stringstream & body, std::string & line) {
    std::string filename;

    if (line.find("filename=") == std::string::npos) {
        line.clear();
        if (std::getline(body, line))
            filename = getFileName(body, line);
        else
            return "";
    } else {
        if (line.find("filename=") != std::string::npos) {
            filename = line.substr(line.find("filename=") + 10);
            filename = filename.substr(0, filename.find("\""));
        }
    }
    return filename;
}

void    Respons::uploadFile(std::stringstream & body, std::string & boundary) {
    std::string line;
    std::string filename;
    std::ofstream file;
    std::string allPathOfFile;

    if (std::getline(body, line)) {
        filename = getFileName(body, line); 
        line.clear();
        if (!std::getline(body, line))
            return ;
        else {
            line.clear();
            if (!std::getline(body, line))
                return ;
        }
        if (_server.currentLocation().uploadDir().empty())
            allPathOfFile = getCurrentPath() + "/" + filename;
        else
            allPathOfFile = _server.currentLocation().uploadDir() + "/" + filename;
        
        file.open(allPathOfFile.c_str(), std::ios::out | std::ios::binary);
        if (file.is_open()) {
            while (std::getline(body, line) && line.find(boundary) == std::string::npos) {
                file << line << std::endl;
            }
            file.close();
        }
        else {
            std::cout << "Error cant open file" << std::endl;
        }
    }
}

void    Respons::handleUpload(void) {
    std::string         contentType = _request.getHeaders()["Content-Type"];
    std::string         boundary    = contentType.substr(contentType.find("boundary=") + 9);
    std::stringstream   body(_request.getBody());

    while (!body.eof()) {
        uploadFile(body, boundary);
    }
}

void    Respons::servPost(void) {
    if (checkResource()) 
        return servErrorPage();

    if (locationSupportUpload()) 
        return handleUpload();

    if (_request.getFileExtension().empty()) 
        return handleFolder();
    else
        return handleFile(getCurrentPath());
}