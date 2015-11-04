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
    std::vector<unsigned char> tmp;

    tmp = client->read(0);
    std::cout << "Received message from " << client->getIp() << " for client no : " << client->getId() << " (msg_length : " << tmp.size() << ") : ";
    for (unsigned int i = 0; i < tmp.size(); i++)
        std::cout << static_cast<char>(tmp[i]);
    std::cout << std::endl;
}

void testOnConnect(ISocket *client)
{
    std::cout << "Server on " << client->getIp() << " for client no : " << client->getId() << " accepted connection!" << std::endl;
}

int main(int ac, char **av)
{
    int port;
    Packet *p;

    srand(time(NULL));

    std::cout << "Test d'envoi de cle publique :" << std::endl;
    Rsa *r = new Rsa();
    p = new Packet(*r);

    std::vector<unsigned char> *data = p->build();
    //envoi
    //reception
    std::cout << "Key received!" << std::endl;
    Packet *a;
    if ((a = Packet::fromStream(*data)) == NULL) {

        std::cout << "failed";
        return (0);
    }
    Rsa *pub = a->unpack<Rsa>();
    std::vector<unsigned char> key = pub->getPublicKey();
    for (unsigned int i = 0; i < key.size(); i++)
        std::cout << key[i];
    std::cout << std::endl;

    std::cout << "Test d'envoi de string cryptee" << std::endl;

    std::string s = "hey";
    std::cout << "envoi de \"" << s << "\"" << std::endl;
    p = new Packet(s);
    data = p->build(pub);
    //envoyer
    std::cout << "crypted data:" << std::endl;
    for (unsigned int i = 0; i < data->size(); i++)
        std::cout << (*data)[i];
    std::cout << std::endl;
    //recevoir
    p = Packet::fromStream(*data, r);
    std::cout << "received string : \"" << *(p->unpack<std::string>()) << "\"" << std::endl;
    return (0);

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
            packet.clear();
            for (unsigned int i = 0; i < s.size(); i++)
                packet.push_back(static_cast<unsigned char>(s[i]));
            packet.push_back(static_cast<unsigned char>('\n'));
            client->write(packet);
        }
        client->cancel();
        sleep(1);
    }
    catch (const char *e) {
        std::cout << e << std::endl;
    }
    return (0);
}