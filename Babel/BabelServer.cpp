//
// Created by rustam_t on 11/4/15.
//

#include "BabelServer.hpp"

BabelServer *
BabelServer::getInstance(bool del)
{
    static BabelServer *_this;

    if (_this == NULL) {

        if (!del)
            _this = new BabelServer();
    }
    else if (del)
    {
        delete _this;
        _this = NULL;
    }
    return (_this);
}

void
BabelServer::deleteProfile(Profile *to_delete)
{
    IMutex *mutex = (*MutexVault::getMutexVault())["people"];

    if (to_delete == NULL)
        return;
    mutex->lock(true);
    for (unsigned int i = 0; i < this->_people.size(); i++)
        if (this->_people[i] != NULL && to_delete == this->_people[i])
        {
            delete this->_people[i]->second;
            delete this->_people[i];
            this->_people[i] = NULL;
            break;
        }
    mutex->unlock();
    return;
}

void
BabelServer::showConnectedUsers()
{
    IMutex *mutex = (*MutexVault::getMutexVault())["people"];
    unsigned int count = 0;

    mutex->lock(true);
    for (unsigned int i = 0; i < this->_people.size(); i++)
        if (this->_people[i] != NULL)
            count += 1;

    if (count == 0)
        std::cout << "No one is connected!" << std::endl;
    else
        std::cout << count << " people are connected!" << std::endl;

    for (unsigned int i = 0; i < this->_people.size(); i++)
        if (this->_people[i] != NULL)
            std::cout << "On " << this->_people[i]->first->getIp() << ", username " << this->_people[i]->second->getUsername() << std::endl;
    mutex->unlock();
    return;
}

BabelServer::Profile *
BabelServer::getByUsername(char *username)
{
    IMutex *mutex = (*MutexVault::getMutexVault())["people"];
    Profile *p = NULL;

    if (username == NULL)
        return (p);
    mutex->lock(true);
    for (unsigned int i = 0; i < this->_people.size(); i++)
        if (this->_people[i] != NULL &&
            strcmp(this->_people[i]->second->getUsername(), username) == 0)
        {
            p = this->_people[i];
            break;
        }
    mutex->unlock();
    return (p);
}

BabelServer::Profile *
BabelServer::getByIdentity(Identity *id)
{
    IMutex *mutex = (*MutexVault::getMutexVault())["people"];
    Profile *p = NULL;

    if (id == NULL)
        return (p);
    mutex->lock(true);
    for (unsigned int i = 0; i < this->_people.size(); i++)
        if (this->_people[i] != NULL && id == this->_people[i]->second)
        {
            p = this->_people[i];
            break;
        }
    mutex->unlock();
    return (p);
}

BabelServer::Profile *
BabelServer::getByClient(ISocket *client)
{
    IMutex *mutex = (*MutexVault::getMutexVault())["people"];
    Profile *p = NULL;

    if (client == NULL)
        return (p);
    mutex->lock(true);
    for (unsigned int i = 0; i < this->_people.size(); i++)
        if (this->_people[i] != NULL && client == this->_people[i]->first)
        {
            p = this->_people[i];
            break;
        }
    mutex->unlock();
    return (p);
}

void
BabelServer::sendPacketToAllRegisteredUsers(Packet *p, ISocket *except)
{
    IMutex *mutex;

    mutex = (*MutexVault::getMutexVault())["people"];
    mutex->lock(true);
    for (unsigned int i = 0; i < this->_people.size(); i++)
        if (this->_people[i] != NULL && (this->_people[i]->first != except))
            this->_people[i]->first->writePacket(p, 0, false);
    delete p;
    mutex->unlock();
}

void
BabelServer::onDisconnect(ISocket *client)
{
    IMutex *mutex = (*MutexVault::getMutexVault())["people"];
    BabelServer *server = BabelServer::getInstance();
    std::cout <<  "Client no : " << client->getId() << " from " << client->getIp() << " disconnected!" << std::endl;
    BabelServer::Profile *client_profile;
    BabelServer::Profile *peer_profile;

    mutex->lock(true);
    if ((client_profile = server->getByClient(client)) != NULL) {

        //announce to peer
        if ((peer_profile = server->getByIdentity(client_profile->second->getPeer())) != NULL)
        {
            peer_profile->second->setPeer(NULL);
            peer_profile->first->writePacket(new Packet(ENDCALL));
        }

        //..announce those sad news to everybody!
        Identity i(client_profile->second->getUsername(), DELCONTACT);

        server->sendPacketToAllRegisteredUsers(Packet::pack(i), client_profile->first);
        //bye bye!
        server->deleteProfile(client_profile);
    }
    mutex->unlock();
}

void
BabelServer::executeInstruction(Instruct *instruct, ISocket *client)
{
    IMutex *mutex = (*MutexVault::getMutexVault())["people"];
    BabelServer *server = BabelServer::getInstance();
    BabelServer::Profile *client_profile;
    BabelServer::Profile *peer_profile;

    mutex->lock(true);
    if ((client_profile = server->getByClient(client)) != NULL)
        switch (*instruct)
        {
            case (DECONNECTION) :
                client->cancel();
                break;
            case (CALLFAILED) :
                *instruct = ENDCALL;
            case (ENDCALL) :
                if ((peer_profile = server->getByIdentity(client_profile->second->getPeer())) == NULL ||
                    (peer_profile->second->getPeer() != client_profile->second))
                {
                    client_profile->first->writePacket(new Packet(KO));
                    return;
                }
                client_profile->first->writePacket(new Packet(OK));
                peer_profile->first->writePacket(new Packet(ENDCALL));
                client_profile->second->setPeer(NULL);
                peer_profile->second->setPeer(NULL);
                break;
        }
    delete instruct;
    mutex->unlock();
}

void
BabelServer::executeIdentity(Identity *identity, ISocket *client)
{
    IMutex *mutex = (*MutexVault::getMutexVault())["people"];
    BabelServer *server = BabelServer::getInstance();
    BabelServer::Profile *client_profile;
    BabelServer::Profile *peer_profile;

    if (identity == NULL)
        return;
    mutex->lock(true);
    switch (identity->getInstruct()) {
        case (CONNECTION) :
            if ((client_profile = server->getByClient(client)) == NULL &&
                identity->hasAdressAndName() && server->getByUsername(identity->getUsername()) == NULL)
            {
                server->_people.push_back(new Profile(client, identity));
                Identity id(identity->getUsername(), ADDCONTACT);
                client->writePacket(new Packet(OK));
                server->sendPacketToAllRegisteredUsers(new Packet(id), client);
                std::cout << "Welcome, " << identity->getUsername() << "!" << std::endl;
                mutex->unlock();
                return;
            }
            else
                client->writePacket(new Packet(KO));
            break;
        case (ASKCALL) :
            if ((client_profile = server->getByClient(client)) != NULL && identity->hasName() &&
                (peer_profile = server->getByUsername(identity->getUsername())) != NULL &&
                peer_profile != client_profile &&
                (client_profile->second->getPeer() == NULL && peer_profile->second->getPeer() == NULL)) {
                client_profile->second->setPeer(peer_profile->second);
                peer_profile->second->setPeer(client_profile->second);

                peer_profile->second->setInstruct(OK);
                client_profile->first->writePacket(new Packet(*(peer_profile->second)));
                client_profile->second->setInstruct(ASKCALL);
                peer_profile->first->writePacket(new Packet(*(client_profile->second)));
            }
            else
                client->writePacket(new Packet(KO));
    }
    delete identity;
    mutex->unlock();
}

void
BabelServer::onReceive(ISocket *client)
{
    Packet  *packet;
    bool    res = true;

    //get packet
    if ((packet = client->readPacket(0)) != NULL) {
        //but first, let me take a RSA
        Rsa *rsa;
        if ((rsa = client->getSendRsa()) == NULL) {
            if (packet->getType() == Packet::SSLPublicKey) {
                if (packet->isEncrypted())
                    client->attachRsa(packet->unpack<Rsa>(client->getRecvRsa()));
                else
                    client->attachRsa(packet->unpack<Rsa>());

                std::cout << "Ok for public key for " << client->getIp() << std::endl;
            }
            else
                res = false;
        }
        else {

            std::vector<unsigned char> k = client->read(0);
            if (packet->getType() == Packet::Id)
                BabelServer::executeIdentity(packet->unpack<Identity>(), client);
            else if (packet->getType() == Packet::Inst)
                BabelServer::executeInstruction(packet->unpack<Instruct>(), client);
            else if (packet->getType() == Packet::String) {

                std::string *msg = packet->unpack<std::string>();
                std::cout << "Received message from " << client->getIp() << " for client no : " << client->getId() <<
                " (msg_length : " << msg->size() << ") : ";
                std::cout << *msg << std::endl;
                delete msg;
            }
            else
                res = false;
        }

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

void
BabelServer::onConnect(ISocket *client)
{
    //greet the client
    std::cout << "Client on " << client->getIp() << ", no : " << client->getId() << " connected!" << std::endl;
    //send brand new, fresh RSA
    Packet *p = new Packet(*(client->getRecvRsa()));
    client->writePacket(p);
}