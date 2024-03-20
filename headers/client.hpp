#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include"../headers/parameters.hpp"

class Client {
private:
    int sockfd;
    struct sockaddr_in server_addr;

public:
    Client(const char* server_ip, int port);
    ~Client();

    bool connectToServer();
    bool sendMessage(const char* message);
    bool receiveResponse(char* buffer, int buffer_size);
};

#endif