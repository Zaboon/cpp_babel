//
// Created by rustam_t on 10/6/15.
//

#include <iostream>
#include <string>
#include <unistd.h>
#include "../IThread.hpp"
#include "LinuxThread.hpp"
#include "../Packet.h"
#include "LinuxSocket.h"

void testOnReceive(ISocket *client)
{
    std::vector<unsigned char> tmp;

    tmp = client->read(0);
    std::cout << "received message from " << client->getIp() << " (length : " << tmp.size() << ") : ";
    for (unsigned int i = 0; i < tmp.size(); i++)
        std::cout << static_cast<char>(tmp[i]);
    std::cout << std::endl;
}

void testOnConnect(ISocket *client)
{
    std::cout << "I am alive!" << std::endl;
}

int main()
{
    LinuxSocket *server = new LinuxSocket(4242);
    std::cout << "Server up and ready on " << server->getIp() << " port " << server->getPort() << " status " << server->getStatus() << std::endl;
    server->attachOnConnect(testOnConnect);
    server->attachOnReceive(testOnReceive);
    server->startServer();
    sleep(1);
    std::cout << "status " << server->getStatus() << std::endl;

    std::string s;
    while (s != "quit")
        std::getline(std::cin, s);
    return (0);
}