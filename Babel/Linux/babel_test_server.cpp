#include <iostream>
#include <unistd.h>
#include <sstream>
#include "../IThread.hpp"
#include "../Packet.h"
#include "../ISocket.h"
#include "../Rsa.h"
#include "LinuxSocket.h"
#include "../BabelServer.hpp"

int     main(int ac, char **av)
{
    int port;

    if (ac != 2)
        return (-1);
    std::istringstream(av[1]) >> port;

    try {
        ISocket *server = ISocket::getServer(port);
        BabelServer *serv = BabelServer::getInstance();

        server->attachOnConnect(BabelServer::onConnect);
        server->attachOnReceive(BabelServer::onReceive);
        server->attachOnDisconnect(BabelServer::onDisconnect);

        server->start();
        std::cout << "Server up and ready on " << server->getIp() << " port " << server->getPort() << " status " << server->getStatus() << std::endl;

        std::string s;
        while (s != "quit") {
            std::getline(std::cin, s);

            if (s == "users")
                serv->showConnectedUsers();
            else
                server->writePacket(Packet::pack<std::string>(s));
        }
        server->cancel();
        BabelServer::getInstance(true);
        sleep(1);
        //delete server;
        //delete serv;
    }
    catch (const char *e) {
        std::cout << e << std::endl;
    }
}