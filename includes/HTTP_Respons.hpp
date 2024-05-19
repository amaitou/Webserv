/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTP_Respons.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 09:57:19 by rlabbiz           #+#    #+#             */
/*   Updated: 2024/05/18 11:52:06 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RESPONS_HPP
# define RESPONS_HPP

// # include "./TCP_Connection.hpp"

# include "./HTTP_Request.hpp"
# include "./Config.hpp"
# include <sys/stat.h>
# include <dirent.h>
# include <unistd.h>
# include <sys/types.h>

class Client;
class Respons {
    private:
        HTTP_Request    _request; // contains servers
        Config          _server;
        int             _clientFd;
        int             _currentPort;
        int             _statusCode;
    
    public:
        Respons();
        ~Respons();

        void        sendRespons(Client & http, Config config);

        // setters
        void    setCurrentPort(int value);
        void    setStatusCode(int value);
        void    setClientFd(int value);

        // Getters
        int     getCurrentPort(void) const;
        int     getStatusCode(void) const;
        int     getClientFd(void) const;

    protected:
        void        sendResponsContent(int fd, std::string content, int statusCode, std::string plain);
        void        servErrorPage(void);
        int         foundCurrentServer(HTTP_Request http, Config config);
        std::string getIp(std::string str);
        int         getPort(std::string str);
        void        sendRedirection(std::string url, int statusCode);
        std::string getStatusCodeString(int statusCode);
        std::string getStatusCodeDescription(int statusCode);

        // locations
        int         checkValidUrl(std::string path);
        int         checkTransferEncoding(void);
        int         checkUrl(std::string path);
        int         handleLocations(void);
        int         checkLocationMethod();
        std::string getMethodString(t_method_type method);
        std::string generateErrorPage(int statusCode);

        // servGet
        void        servGet(void);
        int         checkResource(void);
        std::string getCurrentPath(void);
        void        handleFolder();
        void        handleFile(std::string path);
        void        handleCgi(std::string path="");
        std::string getIndexPath(void);
        void        servAutoIndex(void);
        std::string getExtentionOfFile(std::string );

        // servPost
        void        servPost(void);
        int         locationSupportUpload(void);
        void        handleUpload(void);
        void        uploadFile(std::stringstream & body, std::string & boundary);
        std::string getFileName(std::stringstream & body, std::string & line);

        // servDelete
        void        servDelete(void);


};

#endif
