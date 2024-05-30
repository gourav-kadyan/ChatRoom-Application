#ifndef ClientDetails_HPP
#define ClientDetails_HPP

#include <string>
#include <thread>

struct ClientDetails {
    int id;
    std::string name;
    int socket;
    std::thread th;
};

#endif // ClientDetails_HPP
