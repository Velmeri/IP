#pragma once
#include "Socket.h"

class ServerSocket : public Socket
{
public:
    void StartHosting(int port);
    void Listen();
    void Bind(int port);
};

void ServerSocket::StartHosting(int port)
{
    Bind(port);
    Listen();
}

void ServerSocket::Listen()
{
    cout << "Waiting for client..." << endl;

    //If socket activation fails in listen mode
    //output an error
    if (listen(_socket, 1) == SOCKET_ERROR)
    {
        cout << "Listening error\n";
        system("pause");
        WSACleanup();
        exit(15);
    }
    /*
    The method is blocking. We are waiting for the client to connect.
    As soon as the client connects, the accept function returns
    A new socket through which data is exchanged.
    */
    acceptSocket = accept(_socket, NULL, NULL);
    while (acceptSocket == SOCKET_ERROR)
    {
        acceptSocket = accept(_socket, NULL, NULL);
    }
    _socket = acceptSocket;
}

void ServerSocket::Bind(int port)
{
    //Specify the IPv4 address family
    addr.sin_family = AF_INET;
    /* Convert the address "0.0.0.0" to the correct
    address storage structure, the result is stored in the sin_addr field */
    inet_pton(AF_INET, "0.0.0.0", &addr.sin_addr);
    //Specify the port.
    //function htons converts the number into
    //network byte order
    addr.sin_port = htons(port);

    cout << "Binding to port: " << port << endl;
    //If the bind to the port fails, output an error message
    if (bind(_socket, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR)
    {
        cout << "Failed to bind to port\n";
        system("pause");
        WSACleanup();
        exit(14);
    }
}