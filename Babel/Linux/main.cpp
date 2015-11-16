//
// Created by rustam_t on 10/6/15.
//

#include <iostream>
#include <unistd.h>
#include <sstream>
#include "../IThread.hpp"
#include "../Packet.h"
#include "../ISocket.h"
#include "../Rsa.h"
#include "LinuxSocket.h"

void testOnDisconnect(ISocket *client)
{
    std::cout <<  "Client no : " << client->getId() << " from " << client->getIp() << " disconnected!" << std::endl;
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

    if (ac != 2)
        return (-1);
    std::istringstream(av[1]) >> port;
    try {
        ISocket *server = ISocket::getServer(port);
        std::vector<unsigned char> packet;

        server->attachOnConnect(testOnConnect);
        server->attachOnReceive(testOnReceive);
        server->attachOnDisconnect(testOnDisconnect);

        server->start();
        std::cout << "Server up and ready on " << server->getIp() << " port " << server->getPort() << " status " << server->getStatus() << std::endl;

        std::string s;
        while (s != "quit") {
            std::getline(std::cin, s);x
            server->writePacket(Packet::pack<std::string>(s));
        }
        server->cancel();
        sleep(1);
    }
    catch (const char *e) {
        std::cout << e << std::endl;
    }
    return (0);
}