#ifndef SERVER_CPP
#define SERVER_CPP

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include"../headers/server.hpp"

Server::Server(int port) : port(port) {}

void Server::start(){
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSocket == -1){
        std::cerr << "Error: unable to create socket\n";
        exit(1);
    }
    // Set server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    // Bind socket
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Error: Bind failed\n";
        exit(1);
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) < 0) {
        std::cerr << "Error: Listen failed\n";
        exit(1);
    }

    std::cout << "Server listening on port " << port << "...\n";

    // Accept incoming connection
    clientAddrLen = sizeof(clientAddr);
    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
    if (clientSocket < 0) {
        std::cerr << "Error: Accept failed\n";
        exit(1);
    }

    std::cout << "Connection accepted from " << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << "\n";

    // Handle client communication
    // handleClient();
}

Server::~Server() {
    // Close sockets
    close(clientSocket);
    close(serverSocket);
}

void Server::handleClient() {
    char buffer[1024] = {0};
    int valread;

    while (true) {
        // Receive data from client
        valread = read(clientSocket, buffer, sizeof(buffer));
        if (valread <= 0) {
            std::cerr << "Error: Connection closed by client\n";
            break;
        }

        std::cout << "Message from client: " << buffer << std::endl;

        // Echo back to client
        send(clientSocket, buffer, strlen(buffer), 0);
    }
}

int Server::get_clientSocket(){
    return this->clientSocket;
}

#endif