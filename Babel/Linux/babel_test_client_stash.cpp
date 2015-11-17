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
        server->attachOnDisconnect(BabelClient::onDisconnect);
        //not logged yet ;)
        server->attachOnReceive(BabelClient::onReceiveNotLogged);

        server->start();

        std::string s;
        std::string peername;
        Identity *id;
        while (s != "quit") {

            if (s != "") {

                if (!cl->isConnected()) {
                    cl->enterUsername(s, server);
                }
                else if (s.size() > 5 && s.compare(0, 5, "call ") == 0)
                {
                    peername.empty();
                    for (unsigned int i = 5; i < s.size(); i++)
                        peername.push_back(s[i]);
                    cl->call(peername, server);
                }
                else if (server->getSendRsa() != NULL)
                    server->writePacket(Packet::pack<std::string>(s));
            }
            std::getline(std::cin, s);
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