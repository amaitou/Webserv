/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTP_Respons.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 09:57:19 by rlabbiz           #+#    #+#             */
/*   Updated: 2024/05/21 15:18:39 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef HTTP_RESPONS_HPP
# define HTTP_RESPONS_HPP

# include "./HTTP_Request.hpp"
# include "./Config.hpp"
# include <sys/stat.h>
# include <dirent.h>
# include <unistd.h>
# include <sys/types.h>

# include "CGI_Response.hpp"

class Client;

struct Result {
    std::string     responseContent;
    CGI_Response*   cgi_response;


    Result(std::string response);
    Result(CGI_Response* response);
};


class Respons {
    private:
        HTTP_Request    _request;
        Config          _server;
        int             _clientFd;
        int             _currentPort;
        int             _statusCode;
        std::string     _responsContent;
    
    public:
        Respons();
        ~Respons();

        Result  sendRespons(Client & http, Config config);

        // setters
        void    setCurrentPort(int value);
        void    setStatusCode(int value);
        void    setClientFd(int value);
        void    setResponsContent(std::string value);

        // Getters
        int         getCurrentPort(void) const;
        int         getStatusCode(void) const;
        int         getClientFd(void) const;
        std::string getResponsContent(void) const;

    protected:
        void        sendResponsContent(std::string content, int statusCode, std::string plain);
        void        servErrorPage(void);
        int         foundCurrentServer(HTTP_Request http, Config config);
        std::string getIp(std::string str);
        int         getPort(std::string str);
        void        sendRedirection(std::string url, int statusCode);
        std::string getStatusCodeString(int statusCode);
        std::string getStatusCodeDescription(int statusCode);
        void        servTheDefaultPage(void);

        // locations
        int         checkValidUrl(std::string path);
        int         checkTransferEncoding(void);
        int         checkUrl(std::string path);
        int         handleLocations(void);
        int         checkLocationMethod();
        std::string getMethodString(t_method_type method);
        std::string generateErrorPage(int statusCode);

        // servGet
        Result        servGet(void);
        int         checkResource(void);
        std::string getCurrentPath(void);
        Result        handleFolder();
        Result        handleFile(std::string path);
        Result        handleCgi(std::string path="");
        std::string getIndexPath(void);
        void        servAutoIndex(void);
        std::string getExtentionOfFile(std::string );

        // servPost
        Result        servPost(void);
        int         locationSupportUpload(void);
        void        handleUpload(void);
        void        uploadFile(std::stringstream & body, std::string & boundary);
        std::string getFileName(std::stringstream & body, std::string & line);

        // servDelete
        void        servDelete(void);


};

#endif
