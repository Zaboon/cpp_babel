//
// Created by rustam_t on 11/4/15.
//

#ifndef CPP_BABEL_BABELSERVER_HPP
#define CPP_BABEL_BABELSERVER_HPP

#include "ISocket.h"
#include "MutexVault.hpp"
#include "Packet.h"
#include "Identity.hpp"

#define TRY_LIMIT 10

class BabelServer {

public:

    static BabelServer *getInstance()
    {
        static BabelServer *_this;

        if (_this == NULL)
            _this = new BabelServer();
        return (_this);
    }

    Identity *getPeopleByClient()
    {

    }

    static void onDisconnect(ISocket *client)
    {
        IMutex *mutex;
        std::cout <<  "Client no : " << client->getId() << " from " << client->getIp() << " disconnected!" << std::endl;

        //if client was id...
        mutex = (*MutexVault::getMutexVault())["people"];
        mutex->lock(true);
        if (BabelServer::getInstance()->_people[client] != NULL) {

            //..announce those sad news to everybody!
            this->_people[client]->setInstruct(Instruct::DELCONTACT);
            Packet p(Instruct::DELCONTACT);
            std::vector<unsigned char> *pack = p.build();
            ISocket::getServer()->write(*pack);
            delete pack;
            this->_people[client] = NULL;
        }
        mutex->unlock();
    }

    static void onConnect(ISocket *client)
    {
        //greet the client
        std::cout << "Client on " << client->getIp() << ", no : " << client->getId() << " connected!" << std::endl;
        //send brand new, fresh RSA
        Packet p(*(client->getRecvRsa()));
        std::vector<unsigned char> *pack = p.build();
        client->write(*pack);
        delete pack;
        client->setMustRecvEnc(true);
    }

    static void executeIdentify(Identity *identity, ISocket *client)
    {

    }

    static void onReceive(ISocket *client)
    {
        Packet  *packet;
        bool    res = true;

        //get packet
        if ((packet = Packet::fromStream(client->read(0))) != NULL) {
            //but first, let me take a RSA
            if ((Rsa *rsa = client->getSendRsa()) == NULL) {
                if (!packet->isEncrypted() && packet->getType() == Packet::SSLPublicKey)
                    client->attachRsa(packet->unpack<Rsa>());
                else
                    res = false;
            }
            else if (packet->isEncrypted()) {

                if (packet->getType() == Packet::Identity)
                    BabelServer::executeIdentity(packet->unpack<Identity>(rsa), client);
                else if (packet->getType() == Packet::Instruction)
                    BabelServer::executeInstruction(packet->unpack<Instruction>(rsa), client);
                else
                    res = false;
            }
            else
                res = false;

            delete packet;
        }
        else
            res = false;

        if (!res) {

            if (++this->_tries[client] >= TRY_LIMIT)
                client->cancel();
            else
                this->_tries = 0;
        }
    }

private:

    BabelServer() {};

    std::map<ISocket *, Identity *> _people;
    std::map<ISocket *, unsigned int> _tries;
};


#endif //CPP_BABEL_BABELSERVER_HPP
