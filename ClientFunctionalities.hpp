#ifndef CLIENTFUNCTIONALITIES_HPP
#define CLIENTFUNCTIONALITIES_HPP

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
#include <cstring>
#define MAX_LEN 200
#define NUM_COLORS 6

void catch_ctrl_c(int signal);
std::string color(int code);
void eraseText(int cnt);
void send_message(int client_socket);
void recv_message(int client_socket);
void Start(int client_socket);

#endif // CLIENTFUNCTIONALITIES_HPP
