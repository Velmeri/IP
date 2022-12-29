#pragma once
#include <string>
#include "Socket.h"

class User
{
public:
    User(const std::string& username, Socket& socket);
    void SendMessage(const std::string& message);

private:
    std::string m_username;
    Socket& m_socket;
    unsigned short color;
};

User::User(const std::string& username, Socket& socket) :
    m_username(username), m_socket(socket)
{
    color = 10 + rand() % ((15 + 1) - 10);
}

void User::SendMessage(const std::string& message)
{
    // Construct the message in the format: "username: message"
    std::string messageToSend = m_username + ": " + message;
    // Send the message through the socket
    m_socket.SendData(messageToSend);
}