---
<img width="2560" alt="Screen Shot 2024-05-30 at 3 08 25 AM" src="https://github.com/amaitou/Webserv/assets/49293816/8311fefc-e3e9-4d66-8667-253299a47938">

---
# Overview

- [Webserv](https://github.com/amaitou/Webserv?tab=readme-ov-file#webserv)
  - [Contribution](https://github.com/amaitou/Webserv?tab=readme-ov-file#contribution)
- [Structure](https://github.com/amaitou/Webserv?tab=readme-ov-file#structure)
- [Usage](https://github.com/amaitou/Webserv?tab=readme-ov-file#usage)
- [Config File](https://github.com/amaitou/Webserv?tab=readme-ov-file#config-file)
   - [Server Configuration](https://github.com/amaitou/Webserv?tab=readme-ov-file#server-configuration)
   - [Location Blocks](https://github.com/amaitou/Webserv?tab=readme-ov-file#location-blocks)

---

# Webserv
This project is here to make you write your own HTTP server. You will be able to test it with a real browser. HTTP is one of the most used protocol on internet. Knowing its arcane will be useful, even if you won't be working on a website.

- ### Contribution

This project was a collaborative effort by three dedicated students, each contributing their expertise to different aspects of its development:

- [Amine Ait Ouazghour (Me)](https://www.linkedin.com/in/amaitou/) : Led the project by setting up the server, designing the logic for the multiplexer, and implementing request parsing for every client connected to the server.
- [Rida Labbiz](https://www.linkedin.com/in/rida-labbiz-320b661b8/) : Played a crucial role in parsing the configuration file and handling the response from each client, ensuring smooth communication and data processing within the system.
- [Ali El Amine](https://www.linkedin.com/in/el-amine-ali-0650b1181/) : Demonstrated exceptional skill in creating the Common Gateway Interface (CGI) for our web server and effectively managing potential errors that could arise during the execution of CGI scripts, such as syntax errors and timeouts.


Their combined efforts and expertise significantly contributed to the success and functionality of this project.

---

# Structure

- Code structre (this is the structure which we have followed to complete the project.)
```mathematica
                          Webserver
                        (project name)
                              │
       ┌───────────────┬───────────────┬
       │               │               │
    Config       TCP_Exceptions  TCP_Connection
                     (class)       (class)
                                       │
                ┌──────────────────────┴──────────────────────┐
                │                                             │
           Multiplexer                                     Servers
                                                         	(map)
                                                             │
                                           ┌─────────────────┴────────────┐
                                           │                              │
                              		Server_Instance                    Clients
                                   		(class)                          (map)
                                           │                              │
                                        Sockets                   Client_Instance
                                        (vector)                       (class)
                                           │                              │
                                        Socket             ┌─────────────┴─────────────┐
                                        (struct)       HTTP_Request           	HTTP_Response
                                                         (Class)                  (Class)
```

- Project files structure (PFS)

```
|____.gitignore
|____includes
| |____CGI.hpp
| |____Client_Instance.hpp
| |____Config.hpp
| |____HTTP_Request.hpp
| |____HTTP_Respons.hpp
| |____Parser.hpp
| |____Server_Instance.hpp
| |____TCP_Connection.hpp
| |____TCP_Exceptions.hpp
|____Makefile
|____README.md
|____sources
| |____CGI
| | |____CGI.cpp
| |____Client_Instance
| | |____Client.cpp
| |____Config_Parser
| | |____config.cpp
| | |____getConfig.cpp
| | |____getLocation.cpp
| |____HTTP_Request
| | |____Checkers.cpp
| | |____Getters.cpp
| | |____Parser.cpp
| | |____Printers.cpp
| | |____Request.cpp
| | |____Setters.cpp
| |____HTTP_Respons
| | |____Getters.cpp
| | |____Locations.cpp
| | |____respons.cpp
| | |____servDelete.cpp
| | |____servGet.cpp
| | |____servPost.cpp
| | |____Setters.cpp
| |____main.cpp
| |____MimeTypes
| | |____mime.types
| |____Server_Instance
| | |____Server.cpp
| |____TCP_Connection
| | |____Banner.cpp
| | |____Connection.cpp
| | |____Multiplexer.cpp
| | |____Socket.cpp
| |____TCP_Exceptions
| | |____TCP_Exceptions.cpp
|__________________________
```
---

# Usage

```sh
# make the project first
make
# run the program
./webserv <config file>
```

---

# Config File

**Webserv** config file defines the behavior of the server, just create your website config file, place it whenever you want and give it as an argument to the compiled program so it can parse it and serve your website properly.

```
server {
    listen 8080 8082 8083 8084 8085 8086 8087
    server_name www.ExtraJuice.com
    host        127.0.0.1
    index       Index.html
    cgi         on
    client_max_body_size 1g
    root        /Users/amait-ou/Desktop/webserv/www
    error_page  404 notFound.html
    autoindex   on

	location /new_page {
		method GET POST DELETE
	}

    
    location /cgi-bin {
        method GET POST DELETE
		upload_dir /Users/amait-ou/Desktop/webserv/www
    }
    
    location /ExtraJuice {
        method GET POST DELETE
    }
    
    location /ExtraJuice/imgs {
        method GET POST DELETE
    }

    location /Error_Pages {
        method GET POST DELETE
    }

}
```

### Server Configuration:

- **listen**: Defines the ports that the server will listen on.
- **server_name**: Sets the domain name for the server.
- **host**: Specifies the IP address the server will bind to.
- **index**: Specifies the default file to serve if no file is specified in the URL.
- **cgi**: Enables CGI scripts.
- **client_max_body_size**: Sets the maximum allowed size of the client request body.
- **root**: Defines the root directory where files will be served from.
- **error_page**: Specifies the page to display for 404 errors.
- **autoindex**: Enables directory listing if no index file is found.

   ---

### Location Blocks:

- **location /new_page**: Defines settings for requests to /new_page URI.
   - **method**: Specifies the allowed HTTP methods for this location block.
- **location /cgi-bin**: Defines settings for requests to /cgi-bin URI.
   - **method**: Specifies the allowed HTTP methods for this location block.
   - **upload_dir**: Specifies the directory where uploaded files will be stored.
- **location /ExtraJuice**: Defines settings for requests to /ExtraJuice URI.
   - **method**: Specifies the allowed HTTP methods for this location block.
- **location /ExtraJuice/imgs**: Defines settings for requests to /ExtraJuice/imgs URI.
   - **method**: Specifies the allowed HTTP methods for this location block.
- **location /Error_Pages**: Defines settings for requests to /Error_Pages URI.
   - **method**: Specifies the allowed HTTP methods for this location block.

---

- # **Contact Me**

* [Twitter][_1]

[_1]: https://twitter.com/amait0u

---