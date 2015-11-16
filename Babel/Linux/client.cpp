//
// Created by rustam_t on 10/6/15.
//

#include <iostream>
#include <unistd.h>
#include <sstream>
#include "../IThread.hpp"
#include "../Packet.h"
#include "../Rsa.h"
#include "../ISocket.h"
#include "LinuxSocket.h"

void testOnDisconnect(ISocket *client)
{
    std::cout << "Server on " << client->getIp() << " for client no : " << client->getId() << " disconnected!" << std::endl;
}

void testOnReceive(ISocket *client)
{
    Packet *p;

    if ((p = client->readPacket(0)) == NULL)
        return;
    if (client->getSendRsa() == 0) {
        Rsa *r;
        if (p->getType() == Packet::SSLPublicKey && (r = p->unpack<Rsa>()) != NULL) {
            client->attachRsa(r);
            std::cout << "ok for public key!" << std::endl;
        }
    }
    else if (p->getType() == Packet::String) {

        std::string *s = p->unpack<std::string>();
        std::cout << "Received message from " << client->getIp() << " for client no : " << client->getId() <<
        " (msg_length : " << s->size() << ") : ";
        std::cout << *s << std::endl;
    }
    std::cout << std::endl;
}

void testOnConnect(ISocket *client)
{
    //send him my RSA
    Packet *p = new Packet(*(client->getRecvRsa()));
    client->writePacket(p);
    std::cout << "Server on " << client->getIp() << " for client no : " << client->getId() << " accepted connection!" << std::endl;
}

int main(int ac, char **av)
{
    int port;

    if (ac != 3)
        return (-1);
    std::istringstream(av[2]) >> port;
    std::string ip = av[1];
    try {
        ISocket *client = ISocket::getClient(ip, port);
        std::vector<unsigned char> packet;

        client->attachOnConnect(testOnConnect);
        client->attachOnReceive(testOnReceive);
        client->attachOnDisconnect(testOnDisconnect);

        if (client->start() == -1)
            std::cout << "Failed to connect to " << client->getIp() << " port " << client->getPort() << " status " << client->getStatus() << std::endl;

        std::string s;
        while (s != "quit") {
            std::getline(std::cin, s);
            client->writePacket(Packet::pack<std::string>(s));
        }
        client->cancel();
        sleep(1);
    }
    catch (const char *e) {
        std::cout << e << std::endl;
    }
    return (0);
}