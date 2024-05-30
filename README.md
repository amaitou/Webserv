---
<img width="2560" alt="Screen Shot 2024-05-29 at 12 38 35 AM" src="https://github.com/amaitou/Webserv/assets/49293816/2536f0da-303e-4011-94e1-d40281d78089">

---

# Webserv
This project is here to make you write your own HTTP server. You will be able to test it with a real browser. HTTP is one of the most used protocol on internet. Knowing its arcane will be useful, even if you won't be working on a website.

---

# Structure

- code structre (this is the structure which we have followed to coomplete the project.)
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

- project files structure

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
