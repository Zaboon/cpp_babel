#include <iostream>
#include <unistd.h>
#include <sstream>
#include "../IThread.hpp"
#include "../Packet.h"
#include "../ISocket.h"
#include "../Rsa.h"
#include "LinuxSocket.h"
#include "../BabelClient.hpp"

SoundManager	*getSound()
{
    static SoundManager *sound = NULL;

    if (sound == NULL)
    {
        sound = new SoundManager;

        Pa_Initialize();
        sound->initAudio();
        sound->startStream();
    }

    return sound;
}

int     main(int ac, char **av)
{
    int port;

    if (ac != 3)
        return (-1);
    std::istringstream(av[2]) >> port;
    std::string ip = av[1];

    try {
        ISocket *server = ISocket::getClient(ip, port);

        getSound();
        server->start();

        while (42) {

            usleep(5);
            server->writePacket(Packet::pack<SoundPacket>(*(getSound()->getStruct())));
        }

        server->cancel();
        sleep(1);
        delete server;
    }
    catch (const char *e) {
        std::cout << e << std::endl;
    }
}
