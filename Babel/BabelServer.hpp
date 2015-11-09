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
        mutex->unlock();
        return (p);
    }

    ISocket *getByIdentity(Identity *id)
    {
        IMutex *mutex;
        ISocket *client = NULL;

        if (id == NULL)
            return (client);
        mutex = (*MutexVault::getMutexVault())["people"];
        mutex->lock(true);
        for (std::map<ISocket *, Identity *>::iterator it = this->_people.begin(); it != this->_people.end(); it++)
            if (it->second == id)
                client = it->first;
        mutex->unlock();
        return (client);
    }

    void sendPacketToAllRegisteredUsers(Packet *p, ISocket *except = NULL)
    {
        IMutex *mutex;

        mutex = (*MutexVault::getMutexVault())["people"];
        mutex->lock(true);
        for (std::map<ISocket *, Identity *>::iterator it = this->_people.begin(); it != this->_people.end(); it++)
            if (except != NULL && it->first == except)
                it->first->writePacket(p, 0, false);
        delete p;
        mutex->unlock();
    }

    static void onDisconnect(ISocket *client)
    {
        IMutex *mutex;
        BabelServer *server = BabelServer::getInstance();
        std::cout <<  "Client no : " << client->getId() << " from " << client->getIp() << " disconnected!" << std::endl;

        //if client was id...
        mutex = (*MutexVault::getMutexVault())["people"];
        mutex->lock(true);
        if (server->_people[client] != NULL) {

            ISocket *peer;
            //announce to peer
            if ((peer = server->getByIdentity(server->_people[client]->getPeer())) != NULL)
            {
                server->_people[peer]->setPeer(NULL);
                peer->writePacket(new Packet(CALLFAILED));
            }
            //..announce those sad news to everybody!
            Identity i(server->_people[client]->getUsername(), DELCONTACT);
            server->sendPacketToAllRegisteredUsers(Packet::pack(i), client);
            server->_people[client] = NULL;
        }
        mutex->unlock();
    }

    static void executeInstruction(Instruct *instruct, ISocket *client)
    {
        IMutex *mutex;
        BabelServer *server = BabelServer::getInstance();

        mutex = (*MutexVault::getMutexVault())["people"];
        mutex->lock(true);
        if (server->_people[client] != NULL)
            switch (*instruct)
            {
                case (DECONNECTION) :
                    client->cancel();
                    break;
                case (ENDCALL) :
                    Identity *one;
                    ISocket *other;
                    if ((one = server->_people[client]->getPeer()) != NULL &&
                        (other = server->getByIdentity(one)) != NULL && server->_people[other]->getPeer() == one)
                    {
                        client->writePacket(new Packet(OK));
                        other->writePacket(new Packet(ENDCALL));
                        one->setPeer(NULL);
                        server->_people[other]->setPeer(NULL);
                    }
            }
        delete instruct;
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
        if (server->_people[client] != NULL)
            switch (identity->getInstruct())
            {
                case (CONNECTION) :
                    if (identity->hasAdressAndName() &&
                        server->getByUsername(identity->getUsername()) == NULL)
                    {
                        server->_people[client] = identity;
                        identity->setInstruct(ADDCONTACT);
                        server->sendPacketToAllRegisteredUsers(new Packet(*identity), client);
                        client->writePacket(new Packet(OK));
                        return;//dont delete identity
                    }
                    else
                        client->writePacket(new Packet(KO));
                    break;
                case (ASKCALL) :
                    if (identity->hasName() &&
                        server->getByUsername(identity->getUsername()) != NULL &&
                        server->getByUsername(identity->getUsername()) != client &&
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
        delete identity;
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
            std::string *msg;
            if ((rsa = client->getSendRsa()) == NULL) {
                if (!packet->isEncrypted() && packet->getType() == Packet::SSLPublicKey)
                    client->attachRsa(packet->unpack<Rsa>());
                else
                    res = false;
            }
            else if (packet->isEncrypted()) {

                if (packet->getType() == Packet::Id)
                    BabelServer::executeIdentity(packet->unpack<Identity>(rsa), client);
                else if (packet->getType() == Packet::Inst)
                    BabelServer::executeInstruction(packet->unpack<Instruct>(rsa), client);
                else
                    res = false;
            }
            else if (packet->getType() == Packet::String)
            {
                msg = packet->unpack<std::string>(rsa);
                std::cout << "Received message from " << client->getIp() << " for client no : " << client->getId() <<
                " (msg_length : " << msg->size() << ") : ";
                std::cout << *msg << std::endl;
                delete msg;
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
        client->writePacket(new Packet(*(client->getRecvRsa())));
    }

private:

    BabelServer() {};

    std::map<ISocket *, Identity *> _people;
    std::map<ISocket *, unsigned int> _tries;
};


#endif //CPP_BABEL_BABELSERVER_HPP
