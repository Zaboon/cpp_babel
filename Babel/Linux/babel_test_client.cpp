#include <iostream>
#include <unistd.h>
#include <sstream>
#include "../IThread.hpp"
#include "../Packet.h"
#include "../ISocket.h"
#include "../Rsa.h"
#include "LinuxSocket.h"
#include "../BabelClient.hpp"

int     main(int ac, char **av)
{
    int port;

    if (ac != 3)
        return (-1);
    std::istringstream(av[2]) >> port;
    std::string ip = av[1];

    try {
        ISocket *server = ISocket::getClient(ip, port);
        BabelClient *cl = BabelClient::getInstance();

        server->attachOnConnect(BabelClient::onConnect);
        server->attachOnReceive(BabelClient::onReceive);
        server->attachOnDisconnect(BabelClient::onDisconnect);

        server->start();
        std::cout << "Server up and ready on " << server->getIp() << " port " << server->getPort() << " status " << server->getStatus() << std::endl;

        std::string s;
        while (s != "quit") {
            std::getline(std::cin, s);
            server->writePacket(Packet::pack<std::string>(s));
        }
        server->cancel();
        sleep(1);
        delete server;
        delete cl;
    }
    catch (const char *e) {
        std::cout << e << std::endl;
    }
}