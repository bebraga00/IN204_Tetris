#ifndef SERVER_HPP
#define SERVER_HPP

#include <netinet/in.h>

class Server{
private:
    int serverSocket;
    int clientSocket;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen;
    int port;

public:
    Server(int port);
    ~Server();
    void start();
    int get_clientSocket();
};

#endif