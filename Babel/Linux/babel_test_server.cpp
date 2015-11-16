#include <iostream>
#include <unistd.h>
#include <sstream>
#include "../IThread.hpp"
#include "../Packet.h"
#include "../ISocket.h"
#include "../Rsa.h"
#include "LinuxSocket.h"
#include "../BabelServer.hpp"

SoundManager	*getSound()
{
    static SoundManager *sound = NULL;

    if (sound == NULL)
    {
        sound = new SoundManager;

        sound->setReceivedRetenc(0);
        sound->setReceivedData(NULL);
        Pa_Initialize();
        sound->initAudio();
        sound->startStream();
    }

    return sound;
}

void	onReceive(ISocket* client)
{
    Packet* packet;
    if ((packet = client->readPacket()) == NULL)
        return;

    std::cout << packet->getType() << " : " << Packet::Sound << std::endl;
    if (packet->getType() == Packet::String)
    {
        std::cout << *(packet->unpack<std::string>()) << std::endl;
    }

    if (packet->getType() == Packet::Sound)
    {
        std::cout << "SOUND" << std::endl;
        SoundPacket *sound = packet->unpack<SoundPacket>();

        getSound()->setReceivedRetenc(sound->retenc);
        getSound()->setReceivedData(sound->data);
    }
}

int     main(int ac, char **av)
{
    int port;

    if (ac != 2)
        return (-1);
    std::istringstream(av[1]) >> port;

    try {
        ISocket *server = ISocket::getServer(port);

        server->attachOnReceive(onReceive);

        getSound();
        server->start();
        std::cout << "Server up and ready on " << server->getIp() << " port " << server->getPort() << " status " << server->getStatus() << std::endl;

        std::string s;
        while (s != "quit") {
            std::getline(std::cin, s);
        }
        server->cancel();
        sleep(1);
        //delete server;
        //delete serv;
    }
    catch (const char *e) {
        std::cout << e << std::endl;
    }
}
