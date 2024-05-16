/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 05:34:21 by amait-ou          #+#    #+#             */
/*   Updated: 2024/05/09 02:52:34 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/HTTP_Request.hpp"

HTTP_Request::HTTP_Request(char *content)
{
	this->content = std::string(content);
	this->request.method = NONE;
}

HTTP_Request::HTTP_Request(void)
{
	this->content = "";
	this->request.method = NONE;
}

HTTP_Request::~HTTP_Request(void) {}

