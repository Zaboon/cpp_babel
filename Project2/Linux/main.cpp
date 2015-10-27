//
// Created by rustam_t on 10/6/15.
//

#include <iostream>
#include <string>
#include <unistd.h>
#include <sstream>
#include "../IThread.hpp"
#include "LinuxThread.hpp"
#include "../Packet.h"
#include "LinuxSocket.h"

void testOnDisconnect(ISocket *client)
{
    std::cout << client->getIp() << "| client no : " << client->getId() << " disconnected!" << std::endl;
}

void testOnReceive(ISocket *client)
{
    std::vector<unsigned char> tmp;

    tmp = client->read(0);
    std::cout << "received message from " << client->getIp() << " client no : " << client->getId() << " (msg_length : " << tmp.size() << ") : ";
    for (unsigned int i = 0; i < tmp.size(); i++)
        std::cout << static_cast<char>(tmp[i]);
    std::cout << std::endl;
}

void testOnConnect(ISocket *client)
{
    std::cout << client->getIp() << "| client no : " << client->getId() << " connected!" << std::endl;
}

int main(int ac, char **av)
{
    int port;

    if (ac != 2)
        return (-1);
    std::istringstream(av[1]) >> port;
    try {
        LinuxSocket *server = new LinuxSocket(port);
        std::vector<unsigned char> packet;

        server->attachOnConnect(testOnConnect);
        server->attachOnReceive(testOnReceive);
        server->attachOnDisconnect(testOnDisconnect);

        server->startServer();
        std::cout << "Server up and ready on " << server->getIp() << " port " << server->getPort() << " status " << server->getStatus() << std::endl;

        std::string s;
        while (s != "quit") {
            std::getline(std::cin, s);
            packet.clear();
            for (unsigned int i = 0; i < s.size(); i++) {
                packet.push_back(static_cast<unsigned char>(s[i]));
            }
            server->write(packet, 0);
        }
        server->cancel();
        sleep(1);
    }
    catch (const char *e) {
        std::cout << e << std::endl;
    }
    return (0);
}