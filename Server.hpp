#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <vector>
#include <mutex>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>

#include<iostream>
class Server{
private:
   int server_socket;
public: 
    Server(){};
    Server(const Server &) = delete; // disabled copy constructor
    Server(Server &&) = delete; // disabled move constructor brand new in C++11
    Server &operator=(const Server &) = delete; // disabled assignment operator
    Server &operator=(Server &&) = delete;     // disabled assignment move operator brand new in C++11
    ~Server() = default;

    int serverSocket() const { return server_socket; }
};

#endif // SERVER_HPP
