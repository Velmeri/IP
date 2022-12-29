#include <iostream>
#include "Socket.h"
#include <thread>
#include "Server.h"
#include "User.h"

int main()
{
    // Create a socket
    Socket socket;
    // Connect to the server
    socket.ConnectToServer("127.0.0.1", 8080);
    // Create a user with the username "Alice" and the socket
    User alice("Alice", socket);
    // Send a message to the server
    alice.SendMessage("Hello, server!");
    // Disconnect from the server
    socket.CloseConnection();
}