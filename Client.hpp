#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <signal.h>
#include <mutex>
#include <iostream>
class Client
{
private:
    int client_socket;

public:
    Client(){}
    Client(const Client &) = delete;            // disabled copy constructor
    Client(Client &&) = delete;                 // disabled move constructor brand new in C++11
    Client &operator=(const Client &) = delete; // disabled assignment operator
    Client &operator=(Client &&) = delete;      // disabled assignment move operator brand new in C++11
    ~Client();

    int clientSocket() const { return client_socket; }
    void setClientSocket(int clientSocket) { client_socket = clientSocket; }

    
};

#endif // CLIENT_HPP
