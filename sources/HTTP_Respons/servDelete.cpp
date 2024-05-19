#include "../../includes/HTTP_Respons.hpp"

void    Respons::servDelete(void) {
    std::string path = getCurrentPath();

    if (checkResource()) 
        return servErrorPage();
    
    if (!_request.getFileExtension().empty()) {
        if (remove(path.c_str()) != 0) {
            setStatusCode(500);
            servErrorPage();
        } else {
            setStatusCode(204);
            sendResponsContent("Remove Succufly", getStatusCode(), "text/plain");
        }
    } else {
        if (_request.getPath()[_request.getPath().length() - 1] != '/') {
            setStatusCode(301);
            return sendRedirection(_request.getPath() + "/", 301);
        }

        if (access(path.c_str(), F_OK) == 0) {
            if (remove(path.c_str()) != 0) {
                setStatusCode(500);
                servErrorPage();
            } else {
                setStatusCode(204);
                sendResponsContent("Remove Succufly", getStatusCode(), "text/plain");
            }
        } else {
            setStatusCode(403);
            servErrorPage();
        }
    }

}