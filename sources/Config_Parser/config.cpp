/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:44:22 by rlabbiz           #+#    #+#             */
/*   Updated: 2024/05/12 13:23:35 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Parser.hpp"

Config::Config() {}
Config::~Config() {}

size_t Config::locationsSize(void) const { return this->_location.size(); }

void    Config::setLocation(Location value) { this->_location.push_back(value); }
void    Config::setCurrentLocation(Location value) {
    if (value.root().empty())
        value.setRoot(this->root());
    if (value.index().size() == 0)
        value.setIndex(this->index());
    if (value.autoIndex().empty())
        value.setAutoIndex(this->autoIndex());
    if (value.cgi().empty())
        value.setCgi(this->cgi());
    if (value.errorPage().size() == 0)
        value.setErrorPages(this->errorPage());
    if (value.alias().empty())
        value.setAlias(this->alias());
    this->_currentLocation = value;
}

std::vector<Location>   Config::location(void) const { return this->_location; }
Location                Config::currentLocation(void) const { return this->_currentLocation; }

Location::Location() {}
Location::~Location() {}

void    Location::setIndex(std::vector<std::string> value) { this->_index = value; }
void    Location::setMethod(std::vector<std::string> value) { this->_method = value; }
void    Location::setRedirection(std::map<std::string, int> value) { this->_redirection = value; }
void    Location::setPath(std::string value) { this->_path = value; }
void    Location::setRoot(std::string value) { this->_root = value; }
void    Location::setCgi(std::string value) { this->_cgiPath = value; }
void    Location::setUploadDir(std::string value) { this->_uploadDir = value; }
void    Location::setAlias(std::string value) { this->_alias = value; }
void    Location::setAutoIndex(std::string value) { this->_autoIndex = value; }
void    Location::setBodySize(size_t value) { this->_bodySize = value; }
void    Location::setErrorPage(std::string key, std::string value) { this->_errorPage[key] = value; }
void    Location::setErrorPages(std::map<std::string, std::string> value) { this->_errorPage = value; }

std::vector<std::string>            Location::index(void) const { return this->_index; }
std::vector<std::string>            Location::method(void) const { return this->_method; }
std::map<std::string, int>&         Location::redirection(void) { return this->_redirection; }
std::map<std::string, std::string>  Location::errorPage(void) const { return this->_errorPage; }
std::string                         Location::root(void) const { return this->_root; }
std::string                         Location::path(void) const { return this->_path; }
std::string                         Location::cgi(void) const { return this->_cgiPath; }
std::string                         Location::uploadDir(void) const { return this->_uploadDir; }
std::string                         Location::alias(void) const { return this->_alias; }
std::string                         Location::autoIndex(void) const { return this->_autoIndex; }
size_t                              Location::bodySize(void) const { return this->_bodySize; }



void    Config::setSeverName(std::vector<std::string> value) { this->_serverName = value; }
void    Config::setRoot(std::string value) { this->_root = value; }
void    Config::setAccessLog(std::string value) { this->_accessLog = value; }
void    Config::setErrorLog(std::string value) { this->_errorLog = value; }
void    Config::setAutoIndex(std::string value) { this->_autoIndex = value; }
void    Config::setDefault(bool value) { this->_isDefault = value; }
void    Config::setIndex(std::vector<std::string> value) { this->_index = value; }
void    Config::setIndex(std::map<std::string, std::string> value) { this->_errorPage = value; }
void    Config::setMimeType(std::map<std::string, std::string> value) { this->_mimeType = value; }
void    Config::setErrorPage(std::string key, std::string value) { this->_errorPage[key] = value; }
void    Config::setListen(std::vector<int> value) { this->_listen = value; }
void    Config::setBodySize(size_t value) { this->_bodySize = value; }
void    Config::setIp(std::string value) { this->_ip = value; }
void    Config::setCgi(std::string value) { this->_cgiPath = value; }
void    Config::setAlias(std::string value) { this->_alias = value; }

std::vector<std::string>            Config::serverName(void) const { return this->_serverName; }
std::string                         Config::root(void) const { return this->_root; }
std::string                         Config::accessLog(void) const { return this->_accessLog; }
std::string                         Config::errorLog(void) const { return this->_errorLog; }
std::vector<std::string>            Config::index(void) const { return this->_index; }
std::map<std::string, std::string>  Config::errorPage(void) { return this->_errorPage; }
std::map<std::string, std::string>  Config::mimeType(void) { return this->_mimeType; }
std::string                         Config::autoIndex(void) const { return this->_autoIndex; }
bool                                Config::isDefault(void) const { return this->_isDefault; }
std::vector<int>                    Config::listen(void) const { return this->_listen; }
size_t                              Config::bodySize(void) const { return this->_bodySize; }
std::string                         Config::ip(void) const { return this->_ip; }
std::string                         Config::cgi(void) const { return this->_cgiPath; }
std::string                         Config::alias(void) const { return this->_alias; }
