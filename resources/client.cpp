#ifndef CLIENT_CPP
#define CLIENT_CPP

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "../headers/client.hpp"

Client::Client(const char* server_ip, int port) {
    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return;
    }

    // Set server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, server_ip, &server_addr.sin_addr);
}

Client::~Client() {
    close(sockfd);
}

bool Client::connectToServer() {
    // Connect to server
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Connection failed" << std::endl;
        return false;
    }
    return true;
}

bool Client::sendMessage(const char* message) {
    // Send message to server
    if (send(sockfd, message, LEN_BUFFER, 0) == -1) {
        std::cerr << "Error sending message" << std::endl;
        return false;
    }
    return true;
}

bool Client::receiveResponse(char* buffer, int buffer_size) {
    // Receive response from server
    int bytes_received = recv(sockfd, buffer, buffer_size, 0);
    if (bytes_received == -1) {
        std::cerr << "Error receiving response" << std::endl;
        return false;
    }
    buffer[bytes_received] = '\0'; // Null-terminate the received data
    return true;
}

int Client::get_sockfd(){
    return this->sockfd;
}

#endif