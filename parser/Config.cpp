/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 10:18:05 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/12/29 12:28:35 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.hpp"

Config::~Config() {}

void    Config::setSeverName(std::string value) { this->_serverName = value; }
void    Config::setRoot(std::string value) { this->_root = value; }
void    Config::setAutoIndex(bool value) { this->_autoIndex = value; }
void    Config::setIndex(std::string value) { this->_index = value; }
void    Config::setListen(int value) { this->_listen = value; }

std::string Config::serverName(void) const { return this->_serverName; }
std::string Config::root(void) const { return this->_root; }
std::string Config::index(void) const { return this->_index; }
bool Config::autoIndex(void) const { return this->_autoIndex; }
int Config::listen(void) const { return this->_listen; }