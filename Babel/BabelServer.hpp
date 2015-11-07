//
// Created by rustam_t on 11/4/15.
//

#ifndef CPP_BABEL_BABELSERVER_HPP
#define CPP_BABEL_BABELSERVER_HPP

#include "ISocket.h"
#include "MutexVault.hpp"
#include "Packet.h"
#include "Rsa.h"
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

    ISocket  *getByIdentity(Identity *identity)
    {
        IMutex *mutex;

        if (identity == NULL)
            return (NULL);
        mutex = (*MutexVault::getMutexVault())["people"];
        mutex->lock(true);
    }

    ISocket *getByUsername(char *username)
    {
        IMutex *mutex;
        ISocket *p = NULL;

        if (username == NULL)
            return (p);
        mutex = (*MutexVault::getMutexVault())["people"];
        mutex->lock(true);
        for (std::map<ISocket *, Identity *>::iterator it = this->_people.begin(); it != this->_people.end(); it++)
        {
            if (strcmp(it->second->getUsername(), username) == 0) {

                p = it->first;
                break;
            }
        }
        return (p);
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
            Identity i(BabelServer::getInstance()->_people[client]->getUsername(), DELCONTACT);
            ISocket::getServer()->writePacket(Packet::pack(i));
            BabelServer::getInstance()->_people[client] = NULL;
        }
        mutex->unlock();
    }

    static void executeIdentity(Identity *identity, ISocket *client)
    {
        IMutex *mutex;
        BabelServer *server = BabelServer::getInstance();

        if (identity == NULL)
            return;
        mutex = (*MutexVault::getMutexVault())["people"];
        mutex->lock(true);
        switch (identity->getInstruct())
        {
            case (CONNECTION) :
                if (server->_people[client] != NULL && identity->hasAdressAndName() &&
                        server->getByUsername(identity->getUsername()) == NULL)
                {
                    server->_people[client] = identity;
                    client->writePacket(new Packet(OK));
                }
                else
                    client->writePacket(new Packet(KO));
                break;
            case (ASKCALL) :
                if (server->_people[client] != NULL && identity->hasName() &&
                        server->_people[client]->getPeer() == NULL)
                {
                    ISocket *peer = server->getByUsername(identity->getUsername());
                    if (server->_people[peer]->getPeer() == NULL)
                    {
                        server->_people[client]->setPeer(server->_people[peer]);
                        server->_people[peer]->setPeer(server->_people[client]);

                        server->_people[client]->setInstruct(OK);
                        peer->writePacket(new Packet(*(server->_people[client])));
                        server->_people[peer]->setInstruct(RCVCALL);
                        client->writePacket(new Packet(*(server->_people[peer])));
                    }
                    else
                        client->writePacket(new Packet(KO));
                }
                else
                    client->writePacket(new Packet(KO));
                break;
        }
        mutex->unlock();
        return;
    }

    static void onReceive(ISocket *client)
    {
        Packet  *packet;
        bool    res = true;

        //get packet
        if ((packet = client->readPacket(0)) != NULL) {
            //but first, let me take a RSA
            Rsa *rsa;
            if ((rsa = client->getSendRsa()) == NULL) {
                if (!packet->isEncrypted() && packet->getType() == Packet::SSLPublicKey)
                    client->attachRsa(packet->unpack<Rsa>());
                else
                    res = false;
            }
            else if (packet->isEncrypted()) {

                if (packet->getType() == Packet::Id)
                    BabelServer::executeIdentity(packet->unpack<Identity>(rsa), client);
//                else if (packet->getType() == Packet::Inst)
//                    BabelServer::executeInstruction(packet->unpack<Instruction>(rsa), client);
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

            if (++BabelServer::getInstance()->_tries[client] >= TRY_LIMIT)
                client->cancel();
            else
                BabelServer::getInstance()->_tries[client] = 0;
        }
    }

    static void onConnect(ISocket *client)
    {
        //greet the client
        std::cout << "Client on " << client->getIp() << ", no : " << client->getId() << " connected!" << std::endl;
        //send brand new, fresh RSA
        Packet *p = new Packet(*(client->getRecvRsa()));
        client->writePacket(p);
    }

private:

    BabelServer() {};

    std::map<ISocket *, Identity *> _people;
    std::map<ISocket *, unsigned int> _tries;
};


#endif //CPP_BABEL_BABELSERVER_HPP
