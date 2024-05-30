#ifndef SERVERFUNCTIONALITIES_HPP
#define SERVERFUNCTIONALITIES_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <vector>
#include <iostream>
#include "ClientDetails.hpp"
#include <string>
#define MAX_LEN 200
#define NUM_COLORS 6

std::string color(int code);
void set_name(int id, char name[]);
void shared_print(std::string str, bool endLine);
void broadcast_message(std::string message, int sender_id);
void broadcast_message(int num, int sender_id);
void end_connection(int id);
// void handle_client(int client_socket, int id);
void handle_client(int client_socket, int id);
void Start(int server_socket);

#endif // SERVERFUNCTIONALITIES_HPP
