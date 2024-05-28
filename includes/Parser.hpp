#ifndef PARSER_HPP
#define PARSER_HPP

#include <unistd.h>
#include <iostream>
#include <vector>
#include <map>
#include <exception>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <cctype>
#include <limits>
#include <exception>
#include "Config.hpp"

class Config;
class Location;

// server
std::string getNewLine(std::string oldLine);
void        getContentOfFile(std::ifstream & file, std::stringstream & content);
int         checkFirstLine(Config & server, std::stringstream & content);
void        completLocation(Config & server, Location & location);
int         checkDublePath(Config & server, Location & location);
int         handleListen(Config & server, std::stringstream & line);
int         handleServerName(Config & server, std::stringstream & line);
int         handleRoot(Config & server, std::stringstream & line);
int         handleIndex(Config & server, std::stringstream & line);
int         handleAccessLog(Config & server, std::stringstream & line);
int         handleErrorLog(Config & server, std::stringstream & line);
int         handleErrorPage(Config & server, std::stringstream & line);
int         handleBodySize(Config & server, std::stringstream & line);
int         handleHost(Config & server, std::stringstream & line);
int         handleAutoIndex(Config & server, std::stringstream & line);
int         handleLocation(Config & server, std::string allLine, std::stringstream & content);
int         handleCgiPath(Config & server, std::stringstream & line);
int         handleAlias(Config & server, std::stringstream & line);
int         checkValidContent(Config & server, std::string & allLine);
int         getServerInfo(Config & server, std::stringstream & content);
int         getServers(std::vector<Config> & servers, std::stringstream & content);
std::vector<Config> getConfig(const char * str, int *error);


// location
int     handleLocationRoot(Location & location, std::stringstream & line);
int     checkFirstLocationLine(Location & location, std::stringstream & line);
int     handleLocationCgiPath(Location & location, std::stringstream & line);
int     handleLocationUploadDir(Location & location, std::stringstream & line);
int     handleLocationAlias(Location & location, std::stringstream & line);
int     handleLocationIndex(Location & location, std::stringstream & line);
int     handleLocationMethod(Location & location, std::stringstream & line);
int     handleLocationReturn(Location & location, std::stringstream & line);
int     handleLocationAutoIndex(Location & location, std::stringstream & line);
int     handleLocationBodySize(Location & location, std::stringstream & line);
int     handleLocationErrorPage(Location & location, std::stringstream & line);
int     checkValidLocatioContent(Location & location, std::string & allLine);
void    setDefualtLocation(Config & server);
std::map<std::string, std::string>      getMimeTypes();


#endif