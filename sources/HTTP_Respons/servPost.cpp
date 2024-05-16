#include "../../includes/HTTP_Respons.hpp"

int Respons::locationSupportUpload(void) {
    std::cout << _request.getBody() << std::endl;
    return 0;
}

void    Respons::servPost(void) {
    if (checkResource()) 
        return servErrorPage();

    if (locationSupportUpload()) 
        return handleCgi();

    if (_request.getFileExtension().empty()) 
        return handleFolder();
    else
        return handleFile(getCurrentPath());
}