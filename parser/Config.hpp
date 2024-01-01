/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 10:18:02 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/12/29 12:17:45 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "../main.hpp"

class Config {
protected:
    std::string _serverName;
    std::string _root;
    std::string _index;
    bool        _autoIndex;
    int         _listen;

public:
    Config();
    virtual ~Config();

    void    setSeverName(std::string value) ;
    void    setRoot(std::string value) ;
    void    setIndex(std::string value) ;
    void    setAutoIndex(bool value) ;
    void    setListen(int value);
    
    virtual std::string serverName(void) const ;
    virtual std::string root(void) const ;
    virtual std::string index(void) const ;
    virtual bool autoIndex(void) const ;
    virtual int listen(void) const ;
};

#endif