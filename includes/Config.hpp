/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:44:25 by rlabbiz           #+#    #+#             */
/*   Updated: 2024/05/18 13:04:42 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "Parser.hpp"

class Location {
private:
    std::string                         _path;
    std::string                         _uploadDir;
    std::string                         _alias;
    std::string                         _root;
    size_t                              _bodySize;
    std::string                         _autoIndex;
    std::vector<std::string>            _index;
    std::vector<std::string>            _method;
    std::map<std::string, int>          _redirection;
    std::map<std::string, std::string>  _errorPage;
    std::string                         _cgi;

public:
    Location();
    ~Location();

    void    setPath(std::string value);
    void    setErrorPage(std::string key, std::string value);
    void    setErrorPages(std::map<std::string, std::string> value);
    void    setAlias(std::string value);
    void    setUploadDir(std::string value);
    void    setCgi(std::string value);
    void    setAutoIndex(std::string value);
    void    setBodySize(size_t value);
    void    setRoot(std::string value);
    void    setIndex(std::vector<std::string> value);
    void    setMethod(std::vector<std::string> value);
    void    setRedirection(std::map<std::string, int> value);

    std::vector<std::string>            index(void) const ;
    std::vector<std::string>            method(void) const ;
    std::map<std::string, int>&         redirection(void) ;
    std::map<std::string, std::string>  errorPage(void) const  ;
    std::string                         path(void) const ;
    std::string                         root(void) const ;
    std::string                         cgi(void) const ;
    std::string                         alias(void) const ;
    std::string                         uploadDir(void) const ;
    std::string                         autoIndex(void) const ;
    size_t                              bodySize(void) const ;

};

class Config {
private:
    std::vector<std::string>            _serverName;
    std::vector<std::string>            _index;
    std::map<std::string, std::string>  _errorPage;
    std::string                         _root;
    std::string                         _accessLog;
    std::string                         _errorLog;
    std::string                         _autoIndex;
    bool                                _isDefault;
    std::vector<int>                    _listen;
    size_t                              _bodySize;
    std::string                         _ip;
    std::string                         _alias;
    std::map<std::string, std::string>  _mimeType;
    std::vector<Location>               _location;
    Location                            _currentLocation;
    std::string                         _cgi;

public:
    Config();
    ~Config();

    
    void    setLocation(Location value);
    void    setCurrentLocation(Location value);
    void    setSeverName(std::vector<std::string> value);
    void    setRoot(std::string value);
    void    setAccessLog(std::string value);
    void    setErrorLog(std::string value);
    void    setIndex(std::vector<std::string> value);
    void    setIndex(std::map<std::string, std::string> value);
    void    setMimeType(std::map<std::string, std::string> value);
    void    setErrorPage(std::string key, std::string value);
    void    setAutoIndex(std::string value);
    void    setDefault(bool value);
    void    setListen(std::vector<int> value);
    void    setBodySize(size_t value);
    void    setIp(std::string value);
    void    setCgi(std::string value);
    void    setAlias(std::string value);
    
    
    size_t                              locationsSize(void) const ;
    std::vector<Location>               location(void) const ;
    Location                            currentLocation(void) const ;
    std::vector<std::string>            serverName(void) const ;
    std::string                         root(void) const ;
    std::string                         accessLog(void) const ;
    std::string                         errorLog(void) const ;
    std::vector<std::string>            index(void) const ;
    std::map<std::string, std::string>  errorPage(void)  ;
    std::map<std::string, std::string>  mimeType(void)  ;
    std::string                         autoIndex(void) const ;
    bool                                isDefault(void) const ;
    std::vector<int>                    listen(void) const ;
    size_t                              bodySize(void) const ;
    std::string                         ip(void) const ;
    std::string                         cgi(void) const ;
    std::string                         alias(void) const ;
};

#endif