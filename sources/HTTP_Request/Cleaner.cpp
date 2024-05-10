// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   Cleaner.cpp                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/05/04 04:00:32 by amait-ou          #+#    #+#             */
// /*   Updated: 2024/05/04 04:01:32 by amait-ou         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../includes/HTTP_Request.hpp"

// void HTTP_Request::cleanMembers(void)
// {
// 	this->content.clear();
// 	this->request.method = NONE;
// 	this->request.get.path.clear();
// 	this->request.get.query.clear();
// 	this->request.get.version.clear();
// 	this->request.get.headers.clear();
// 	this->request.post.path.clear();
// 	this->request.post.query.clear();
// 	this->request.post.version.clear();
// 	this->request.post.content_type = _NONE;
// 	this->request.post.headers.clear();
// 	this->request.post.body.clear();
// }