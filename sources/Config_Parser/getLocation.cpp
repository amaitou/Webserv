#include "../../includes/Parser.hpp"

int handleLocationRoot(Location & location, std::stringstream & line) {
    std::string word;

    line >> word;
    if (word.empty()) {
        std::cerr << "Error: missing the value of 'location_root'." << '\n';
        return 1;
    }

    if (location.root().length() != 0) {
        std::cerr << "Error: cant set tow root rule to location." << '\n';
        return 1;
    }

    if (word.back() == '/' && word.length() != 1)
        word.erase(--word.end());
    if (word.at(0) != '/')
        word.insert(0, "/");

    location.setRoot(word);
    word.clear();
    
    line >> word;
    if (!word.empty()) {
        std::cerr << "Error: cant set two roots to location." << '\n';
        return 1;
    }
    
    return (0);
}

int checkFirstLocationLine(Location & location, std::stringstream & line) {
    std::string word;

    line >> word;
    
    if (word != "location")
        return 1;
    
    word.clear();
    line >> word;

    if (word.empty())
        return 1;
    
    location.setPath(word);
    word.clear();

    line >> word;
    if (word.empty() || word != "{")
        return 1;
    word.clear();

    line >> word;
    if (!word.empty())
        return 1;
    return 0;
}

int handleLocationCgiPath(Location & location, std::stringstream & line) {
    std::string word;

    line >> word;
    if (word.empty()) {
        std::cerr << "Error: missing the value of 'location_cgi'." << '\n';
        return 1;
    }

    if (location.cgi().length() != 0) {
        std::cerr << "Error: cant set two cgi_path rule to location." << '\n';
        return 1;
    }
    
    location.setCgi(word);
    word.clear();
    
    line >> word;
    if (!word.empty()) {
        std::cerr << "Error: cant set two cgi_path to location." << '\n';
        return 1;
    }
    
    return (0);
}

int handleLocationUploadDir(Location & location, std::stringstream & line) {
    std::string word;

    line >> word;
    if (word.empty()) {
        std::cerr << "Error: missing the value of 'location_upload_dir'." << '\n';
        return 1;
    }

    if (location.uploadDir().length() != 0) {
        std::cerr << "Error: cant set two uplaod_dir rule to location." << '\n';
        return 1;
    }

    if (word.back() == '/' && word.length() != 1)
        word.erase(--word.end());
    if (word.at(0) != '/')
        word.insert(0, "/");
    
    location.setUploadDir(word);
    word.clear();
    
    line >> word;
    if (!word.empty()) {
        std::cerr << "Error: cant set two upload_dir to location." << '\n';
        return 1;
    }
    
    return (0);
}

int handleLocationAlias(Location & location, std::stringstream & line) {
    std::string word;

    line >> word;
    if (word.empty()) {
        std::cerr << "Error: missing the value of 'location_alias'." << '\n';
        return 1;
    }

    if (location.alias().length() != 0) {
        std::cerr << "Error: cant set two alias rule to location." << '\n';
        return 1;
    }

    if (word.back() == '/' && word.length() != 1)
        word.erase(--word.end());
    if (word.at(0) != '/')
        word.insert(0, "/");
    
    location.setAlias(word);
    word.clear();
    
    line >> word;
    if (!word.empty()) {
        std::cerr << "Error: cant set two alias to location." << '\n';
        return 1;
    }
    
    return (0);
}

int handleLocationIndex(Location & location, std::stringstream & line) {
    std::vector<std::string>    vector;
    std::string                 word;

    line >> word;
    if (word.empty()) {
        std::cerr << "Error: missing the value of 'location_index'." << '\n';
        return 1;
    }

    vector.push_back(word);
    if (word.back() == '/' && word.length() != 1)
        word.erase(--word.end());
    if (word.at(0) != '/')
        word.insert(0, "/");
    word.clear();
    
    while (line >> word) {
        vector.push_back(word);
        word.clear();
    }
    
    location.setIndex(vector);
    return 0;
}

int handleLocationMethod(Location & location, std::stringstream & line) {
    std::vector<std::string>    vector;
    std::string                 word;

    line >> word;
    if (word.empty()) {
        std::cerr << "Error: missing the value of 'location_method'." << '\n';
        return 1;
    }

    vector.push_back(word);
    word.clear();
    
    while (line >> word) {
        vector.push_back(word);
        word.clear();
    }
    
    location.setMethod(vector);
    return 0;
}

int handleLocationReturn(Location & location, std::stringstream & line) {
    std::map<std::string, int>  loca;
    std::string                 word;
    int                         statusCode;

    line >> word;
    if (word.empty()) {
        std::cerr << "Error: missing the status code of 'location_redirection'." << '\n';
        return 1;
    }
    
    for (size_t i = 0; i < word.length(); i++){
        if (!std::isdigit(word.at(i))) {
            std::cerr << "Error: the status code of 'location_redirection' must contain just number." << '\n';
            return 1;
        }
    }
    
    statusCode = std::atoi(word.c_str());
    word.clear();

    line >> word;
    if (word.empty()) {
        std::cerr << "Error: missing the path of 'location_redirection'." << '\n';
        return 1;
    }
    if (word.back() == '/' && word.length() != 1)
        word.erase(--word.end());
    if (word.at(0) != '/')
        word.insert(0, "/");
    
    loca[word] = statusCode;
    word.clear();
    
    line >> word;
    if (!word.empty()) {
        std::cerr << "Error: invalid 'location_redirection'." << '\n';
        return 1;
    }
    
    if (location.redirection().size() != 0) {
        std::cerr << "Error: must be just one redirection on each location." << '\n';
        return 1;
    }

    location.setRedirection(loca);
    return 0;
}

int handleLocationAutoIndex(Location & location, std::stringstream & line) {
    std::string word;

    line >> word;

    if (word.empty()){
        std::cerr << "Error: missing the value of the lcoation_autoindex." << '\n';
        return 1;
    }
    
    if (word == "on")
        location.setAutoIndex("on");
    else if (word == "off")
        location.setAutoIndex("off");
    else {
        std::cerr << "Error: location_autoindex accept just on or off." << '\n';
        return 1;
    }
    
    word.clear();
    line >> word;

    if (word.length() != 0) {
        std::cerr << "Error: Invalid location_autoindex." << '\n';
        return 1;
    }
    return (0);
}

int handleLocationBodySize(Location & location, std::stringstream & line) {
    std::string word;
    size_t      bodySize;

    line >> word;

    if (word.empty()){
        std::cerr << "Error: missing the value of location_body_size." << '\n';
        return 1;
    }
    
    size_t i = 0;
    for (; i < word.length() - 1; i++) {
        if (!std::isdigit(word.at(i))) {
            std::cerr << "Error: body size must contain just numbers and forma (m or g) at the end." << '\n';
            return 1;
        }
    }

    if (word.at(i) != 'm' && word.at(i) != 'M' && word.at(i) != 'g' && word.at(i) != 'G'){
        std::cerr << "Error: missing the format of body size, format as m or g only." << '\n';
        return 1;
    }
    
    bodySize = std::atol(word.c_str());

    if (word.at(i) == 'm' || word.at(i) == 'M')
        bodySize *= 1048576;
    else 
        bodySize *= 1073741824;
    
    word.clear();
    line >> word;

    if (word.length() != 0) {
        std::cerr << "Error: Invalid body size." << '\n';
        return 1;
    }
    location.setBodySize(bodySize);
    return (0);
}

int handleLocationErrorPage(Location & location, std::stringstream & line) {
    std::string key;
    std::string value;

    line >> key;
    line >> value;
    if (key.empty() || value.empty()) {
        std::cerr << "Error: missing the value of 'location_error_page'." << '\n';
        return 1;
    }

    location.setErrorPage(key, value);
    return 0;
}

int checkValidLocatioContent(Location & location, std::string & allLine) {
    std::stringstream   line(allLine);
    std::string         word;

    line >> word;

    if (word == "root")
        return handleLocationRoot(location, line);
    else if (word == "cgi_path")
        return handleLocationCgiPath(location, line);
    else if (word == "upload_dir")
        return handleLocationUploadDir(location, line);
    else if (word == "alias")
        return handleLocationAlias(location, line);
    else if (word == "index")
        return handleLocationIndex(location, line);
    else if (word == "return")
        return handleLocationReturn(location, line);
    else if (word == "method")
        return handleLocationMethod(location, line);
    else if (word == "client_max_body_size")
        return handleLocationBodySize(location, line);
    else if (word == "autoindex")
        return handleLocationAutoIndex(location, line);
    else if (word == "error_page")
        return handleLocationErrorPage(location, line);
    else {
        std::cerr << "Error: we dont know '" << word << "'.\n";
        return 1;
    }
    
    return 0;
}

std::map<std::string, std::string>      getMimeTypes() {
    std::map<std::string, std::string>  mimeTypes;
    std::ifstream                       file("sources/MimeTypes/mime.types");
    std::string                         line;
    std::string                         word;
    std::stringstream                   content;
    std::stringstream                   tmp;
    std::string                         key;
    std::string                         value;
    
    if (!file.is_open()) {
        std::cout << "cant open MimeTypes File." << '\n';
        return mimeTypes;
    }
    
    while (std::getline(file, line))
        content << line << '\n';
    
    line.clear();
    while (std::getline(content, line)) {
        tmp.clear();
        tmp << line;
        tmp >> value;
        
        while (tmp >> word) {
            key = key +  " " + word;
            word.clear();
        }
        
        mimeTypes[key] = value;

        key.clear();
        value.clear();
        word.clear();
        line.clear();
    }
    file.close();
    return mimeTypes;
}

void setDefualtLocation(Config & server) {
    std::vector<Location>       locations = server.location();
    size_t                      i;
    int                         isExist = 0;
    Location                    defaultLocation;
    std::vector<std::string>    methods;
    
    for (i = 0; i < locations.size(); i++) {
        if (locations[i].path() == "/") {
            server.setCurrentLocation(locations[i]);
            isExist = 1;
            break ;
        }
    }

    if (!isExist) {
        defaultLocation.setPath("/");
        methods.push_back("GET");
        methods.push_back("POST");
        methods.push_back("DELETE");
        defaultLocation.setMethod(methods);
        server.setCurrentLocation(defaultLocation);
    }
}