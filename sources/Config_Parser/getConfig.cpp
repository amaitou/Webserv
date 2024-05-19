/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getConfig.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:32:36 by rlabbiz           #+#    #+#             */
/*   Updated: 2024/05/18 13:04:01 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Parser.hpp"

std::string getNewLine(std::string oldLine) {
    std::string newLine;
    size_t start    = oldLine.find_first_not_of(" \t\n");
    size_t end      = oldLine.find_last_not_of(" \t\n");
    if (start == std::string::npos || end == std::string::npos)
        return newLine;
    return oldLine.substr(start, end - start + 1);
}

void   getContentOfFile(std::ifstream & file, std::stringstream & content) {
    std::string         line;
    std::string         oldLine;
    std::string         newLine;

    while (file) {
        std::getline(file, oldLine);
        newLine = getNewLine(oldLine);
        if (newLine.length() != 0)
            content << newLine << '\n';
        oldLine.clear();
        newLine.clear();
    }
}

int checkFirstLine(Config & server, std::stringstream & content) {
    std::string         allLine;
    std::string         word;
    std::stringstream   line;

    std::getline(content, allLine);

    if (content.fail() || content.eof())
        throw std::out_of_range("");
    
    if (allLine.empty()) {
        std::cerr << "Error." << '\n';
        return 1;
    }

    line << allLine;

    line >> word;
    if (word.empty() || word != "server") {
        std::cerr << "Error: do you mean server ?" << '\n';
        return 1;
    }

    word.clear();
    line >> word;
    if (word.empty() || (word != "default" && word != "{")) {
        std::cerr << "Error: dont know this word '" << word << "'.\n";
        return 1;
    } else {
        if (word == "default") {
            server.setDefault(true);
        } else 
            return 0;
    }
    
    word.clear();
    line >> word;
    if (word.empty() || word != "{"){
        std::cerr << "Error: missing '{'." << '\n';
        return 1;
    }
    
    word.clear();
    line >> word;
    if (!word.empty()) {
        std::cerr << "Error: dont know this word '" << word << "'.\n";
        return 1;
    }
    
    return 0;
}

void    completLocation(Config & server, Location & location) {
    if (!location.root().length())
        location.setRoot(server.root());
    if (!location.index().size())
        location.setIndex(server.index());
}

int checkDublePath(Config & server, Location & location) {
    for (size_t i = 0; i < server.location().size(); i++) {
        if (server.location()[i].path() == location.path())
            return 1;
    }
    return 0;
}

int handleListen(Config & server, std::stringstream & line) {
    std::string         word;
    long                listen;
    // std::vector<int>    ports;

    line >> word;

    if (word.empty()){
        std::cerr << "Error: missing the value of listen." << '\n';
        return 1;
    }
    
    for (size_t i = 0; i < word.length(); i++) {
        if (!std::isdigit(word.at(i))) {
            std::cerr << "Error: listen must contain just numbers." << '\n';
            return 1;
        }
    }
    
    listen = std::atol(word.c_str());
    if (listen > std::numeric_limits<int>::max() || listen < 0) {
        std::cerr << "Error: not valid listen." << '\n';
        return 1;
    }
    server.setListen(static_cast<int>(listen));
    word.clear();
    
    line >> word;
    if (!word.empty()) {
        std::cerr << "Error: not valid listen." << '\n';
        return 1;
    }
    
    return (0);
}

int handleServerName(Config & server, std::stringstream & line) {
    std::string                 word;
    std::vector<std::string>    vector;
    
    line >> word;
    
    if (word.empty()) {
        std::cerr << "Error: missing the value of 'server_name'" << '\n';
        return 1;
    }
    
    vector.push_back(word);
    word.clear();

    while (line >> word) {
        vector.push_back(word);
        word.clear();
    }
    
    server.setSeverName(vector);
    return (0);
}

int handleRoot(Config & server, std::stringstream & line) {
    std::string word;

    line >> word;
    if (word.empty()) {
        std::cerr << "Error: missing the value of 'root'." << '\n';
        return 1;
    }

    if (server.root().length() != 0) {
        std::cerr << "Error: cant set two root rule to server." << '\n';
        return 1;
    }

    if (word.back() == '/' && word.length() != 1)
        word.erase(--word.end());
    if (word.at(0) != '/') {
        word.insert(0, "/");
    }
    
    server.setRoot(word);
    word.clear();
    
    line >> word;
    if (!word.empty()) {
        std::cerr << "Error: cant set two roots." << '\n';
        return 1;
    }
    
    return (0);
}

int handleIndex(Config & server, std::stringstream & line) {
    std::vector<std::string>    vector;
    std::string                 word;

    line >> word;
    if (word.empty()) {
        std::cerr << "Error: missing the value of 'index'." << '\n';
        return 1;
    }

    if (word.back() == '/' && word.length() != 1)
        word.erase(--word.end());
    if (word.at(0) == '/'   && word.length() != 1)
        word.erase(word.begin());
    
    vector.push_back(word);
    word.clear();
    
    while (line >> word) {
        if (word.back() == '/' && word.length() != 1)
            word.erase(--word.end());
        if (word.at(0) == '/'   && word.length() != 1)
            word.erase(word.begin());
        vector.push_back(word);
        word.clear();
    }
    server.setIndex(vector);
    return 0;
}

int handleAccessLog(Config & server, std::stringstream & line) {
    std::string word;

    line >> word;
    if (word.empty()) {
        std::cerr << "Error: missing the value of 'access_log'." << '\n';
        return 1; 
    }

    server.setAccessLog(word);
    word.clear();

    line >> word;
    if (!word.empty()) {
        std::cerr << "Error: cant set more than one 'access_log' file." << '\n';
        return 1; 
    }
    return 0;
}

int handleErrorLog(Config & server, std::stringstream & line) {
    std::string word;

    line >> word;
    if (word.empty()) {
        std::cerr << "Error: missing the value of 'error_log'." << '\n';
        return 1;
    }

    server.setErrorLog(word);
    word.clear();

    line >> word;
    if (!word.empty()) {
        std::cerr << "Error: cant set more than one 'error_log' file." << '\n';
        return 1;
    }

    return 0;
}

int handleErrorPage(Config & server, std::stringstream & line) {
    std::string key;
    std::string value;

    line >> key;
    line >> value;
    if (key.empty() || value.empty()) {
        std::cerr << "Error: missing the value of 'error_page'." << '\n';
        return 1;
    }

    if (value.find("/") != std::string::npos) {
        std::cerr << "Error: value of error page cant contain '/', and accept just a file.\n";
        return 1;
    }

    if (value.back() == '/' && value.length() != 1)
        value.erase(--value.end());
    if (value.at(0) == '/'   && value.length())
        value.erase(value.begin());
    
    server.setErrorPage(key, value);
    return 0;
}

int handleBodySize(Config & server, std::stringstream & line) {
    std::string word;
    size_t        bodySize;

    line >> word;

    if (word.empty()){
        std::cerr << "Error: missing the value of body size." << '\n';
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
    server.setBodySize(bodySize);
    return (0);
}

int handleHost(Config & server, std::stringstream & line) {
    std::string word;
    std::string ip;

    line >> word;

    if (word.empty()){
        std::cerr << "Error: missing the value of host." << '\n';
        return 1;
    }

    for (size_t i = 0; i < word.length(); i++) {
        if (!std::isdigit(word.at(i)) && word.at(i) != '.') {
            std::cerr << "Error: host must contain just numbers." << '\n';
            return 1;
        }
    }

    server.setIp(word);
    
    word.clear();
    line >> word;

    if (word.length() != 0) {
        std::cerr << "Error: Invalid host." << '\n';
        return 1;
    }
    return (0);
}

int handleAutoIndex(Config & server, std::stringstream & line) {
    std::string word;

    line >> word;

    if (word.empty()){
        std::cerr << "Error: missing the value of the autoindex." << '\n';
        return 1;
    }
    
    if (word == "on")
        server.setAutoIndex("on");
    else if (word == "off")
        server.setAutoIndex("off");
    else {
        std::cerr << "Error: autoindex accept just on or off." << '\n';
        return 1;
    }
    
    word.clear();
    line >> word;

    if (word.length() != 0) {
        std::cerr << "Error: Invalid autoindex." << '\n';
        return 1;
    }
    return (0);
}

int handleLocation(Config & server, std::string allLine, std::stringstream & content) {
    std::stringstream   line;
    Location            location;

    line << allLine;
    allLine.clear();
    if (checkFirstLocationLine(location, line)) {
        std::cerr << "Error: invalid location." << '\n';
        return 1;
    }
    line.str("");
    line.clear();
    
    if (checkDublePath(server, location)) {
        std::cerr << "Error: cant set same path for two locations." << '\n';
        return 1;
    }
    
    while (std::getline(content, allLine)) {
        if (allLine.empty()) {
            std::cerr << "Error: missing '}'." << '\n';
            return 1;
        } else if (allLine == "}")
            break ;
        if (checkValidLocatioContent(location, allLine))
            return 1;
        allLine.clear();
    }
    completLocation(server, location);
    
    if (location.method().size() == 0) {
        std::cerr << "Error: each location must has the allowed methods'." << '\n';
        return 1;
    }
    server.setLocation(location);
    return 0;
}

int handleCgi(Config & server, std::stringstream & line) {
    std::string     word;

    line >> word;
    if (word.empty()) {
        std::cerr << "Error: missing the value of cgi." << '\n';
        return 1;
    }

    if (server.cgi().length() != 0) {
        std::cerr << "Error: cant set two cgi rule to server." << '\n';
        return 1;
    }

    if (word != "on" && word != "off") {
        std::cerr << "Error: value of cgi must be on or off." << '\n';
        return 1;
    }
    
    server.setCgi(word);
    word.clear();
    
    line >> word;
    if (!word.empty()) {
        std::cerr << "Error: cant set two cgi to server." << '\n';
        return 1;
    }
    
    return (0);
}

int handleAlias(Config & server, std::stringstream & line) {
    std::string word;

    line >> word;
    if (word.empty()) {
        std::cerr << "Error: missing the value of alias." << '\n';
        return 1;
    }

    if (server.alias().length() != 0) {
        std::cerr << "Error: cant set two alias rule to server." << '\n';
        return 1;
    }

    if (word.back() == '/' && word.length() != 1)
        word.erase(--word.end());
    if (word.at(0) != '/')
        word.insert(0, "/");
    
    server.setAlias(word);
    word.clear();
    
    line >> word;
    if (!word.empty()) {
        std::cerr << "Error: cant set two alias to server." << '\n';
        return 1;
    }
    
    return (0);
}

int checkValidContent(Config & server, std::string & allLine) {
    std::stringstream   line(allLine);
    std::string         word;

    line >> word;
    if (word == "listen")
        return handleListen(server, line);
    else if (word == "server_name")
        return handleServerName(server, line);
    else if (word == "cgi")
        return handleCgi(server, line);
    else if (word == "root")
        return handleRoot(server, line);
    else if (word == "index")
        return handleIndex(server, line);
    else if (word == "alias")
        return handleAlias(server, line);
    else if (word == "access_log")
        return handleAccessLog(server, line);
    else if (word == "error_log")
        return handleErrorLog(server, line);
    else if (word == "error_page")
        return handleErrorPage(server, line);
    else if (word == "client_max_body_size")
        return handleBodySize(server, line);
    else if (word == "host")
        return handleHost(server, line);
    else if (word == "autoindex")
        return handleAutoIndex(server, line);
    else {
        std::cerr << "Error: we dont know '" << word << "'.\n";
        return 1;
    }
    
    return 0;
}

int getServerInfo(Config & server, std::stringstream & content) {
    std::string         allLine;
    std::string         word;
    std::stringstream   line;
    std::string         location;
    
    while (std::getline(content, allLine)) {
        if (allLine.empty()) {
            std::cerr << "Error: missing '}'." << '\n';
            return 1;
        } else if (allLine == "}")
            break ;

        location = allLine.substr(0, 9);
        if (location == "location ") {
            if (handleLocation(server, allLine, content))
                return 1;
        } else if (checkValidContent(server, allLine))
            return 1;
        
        allLine.clear();
    }
    
    return 0;
}

void    setDefaultValues(Config server) {
    if (server.ip().empty())
        server.setIp("0.0.0.0");
    if (server.cgi().empty())
        server.setCgi("on");
}

int getServers(std::vector<Config> & servers, std::stringstream & content) {
    Config server;
    
    if (checkFirstLine(server, content))
        return 1;
    
    if (server.isDefault()) {
        for (size_t i = 0; i < servers.size(); i++) {
            if (servers[i].isDefault()) {
                std::cerr << "Error: cant set default for two servers." << '\n';
                return 1;
            }
        }
    }
    
    if (getServerInfo(server, content))
        return 1;
    
    setDefaultValues(server);
    setDefualtLocation(server);
    
    if (server.isDefault())
        servers.insert(servers.begin(), server);
    else 
        servers.push_back(server);
    
    if (!(content.fail() || content.eof())) {
        if (getServers(servers, content))
            return 1;
    }
    
    return 0;
}

std::vector<Config> getConfig(const char * str, int *error) {
    std::vector<Config>                 servers;
    std::ifstream                       file(str);
    std::string                         oldLine;
    std::stringstream                   content;
    std::map<std::string, std::string>  mimeType;
    
    if (!file.is_open()) {
        std::cerr << "Error: cant open the config file: " << str << '\n';
        *error = 1;
    }
    getContentOfFile(file, content);
    
    try {
        if (getServers(servers, content)) {
            *error = 1;
            file.close();
            return servers;
        }
    } catch (std::exception & e) {}
    
    mimeType = getMimeTypes();

    for (size_t i = 0; i < servers.size(); i++)
        servers[i].setMimeType(mimeType);
    file.close();
    *error = 0;
    return servers;
}