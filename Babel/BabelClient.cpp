//
// Created by rustam_t on 11/11/15.
//

#include "BabelClient.hpp"

BabelClient *
BabelClient::getInstance()
{
    static BabelClient *_this;

    if (_this == NULL)
        _this = new BabelClient;
    return (_this);
}

std::vector<Identity>
BabelClient::getContacts()
{
    IMutex *mutex = (*MutexVault::getMutexVault())["contacts"];
    std::vector<Identity> contacts;

    mutex->lock(true);
    for (unsigned int i = 0; i < this->_contacts.size(); i++)
        if (this->_contacts[i] != NULL)
            contacts.push_back(*(this->_contacts[i]));
    mutex->unlock();
    return (contacts);
}

void
BabelClient::addContact(Identity *id)
{
    IMutex *mutex = (*MutexVault::getMutexVault())["contacts"];

    mutex->lock(true);
    this->_contacts.push_back(id);
    mutex->unlock();
}

void
BabelClient::removeContact(Identity *id)
{
    IMutex *mutex = (*MutexVault::getMutexVault())["contacts"];

    mutex->lock(true);
    for (unsigned int i = 0; i < this->_contacts.size(); i++)
        if (this->_contacts[i] == id)
        {
            delete this->_contacts[i];
            this->_contacts[i] = NULL;
            break;
        }
    mutex->unlock();
}

void
BabelClient::executeIdentity(Identity *id, ISocket *client)
{
    IMutex *mutex;
    BabelClient *_this = BabelClient::getInstance();

    if (id == NULL)
        return;
    switch (id->getInstruct())
    {
        case (ADDCONTACT) :
            BabelClient::getInstance()->addContact(id);
            return; //no delete
        case (DELCONTACT) :
            BabelClient::getInstance()->removeContact(id);
            break;
        case (ASKCALL) :
            mutex = (*MutexVault::getMutexVault())["peer"];
            mutex->lock(true);
            if (id->hasAdressAndName() && _this->_peer == NULL)
            {
                _this->_peer = ISocket::getClient(id->getIp(), id->getPort());
                if (_this->_peer->start() == -1) {
                    std::cout << "Connection failed" << std::endl;
                    client->writePacket(new Packet(ENDCALL));
                    delete _this->_peer;
                    _this->_peer = NULL;
                }
                else
                {

                    //attach handlers
                    client->writePacket(new Packet(CALLESTABLISHED));
                }
            }
            else
                client->writePacket(new Packet(ENDCALL));
            mutex->unlock();
    }
    delete id;
    return;
}

void
BabelClient::executeInstruction(Instruct *instruct, ISocket *client)
{
    IMutex *mutex;
    BabelClient *_this = BabelClient::getInstance();

    if (!instruct)
        return;
    switch (*instruct)
    {
        case (ENDCALL) :
            mutex = (*MutexVault::getMutexVault())["peer"];
            mutex->lock(true);
            if (_this->_peer != NULL)
            {
                _this->_peer->cancel();
                delete _this->_peer;
                _this->_peer = NULL;
            }
            mutex->unlock();
    }
}

void
BabelClient::onConnect(ISocket *client)
{
    Packet *p = new Packet(*(client->getRecvRsa()));
    client->writePacket(p);
    std::cout << "Server on " << client->getIp() << " for client no : " << client->getId() << " accepted connection!" << std::endl;
}

void
BabelClient::onDisconnect(ISocket *client)
{
    BabelClient *_this = BabelClient::getInstance();

    IMutex *mutex = (*MutexVault::getMutexVault())["peer"];
    mutex->lock(true);
    if (_this->_peer != NULL) {
        _this->_peer->cancel();
        delete _this->_peer;
        _this->_peer = NULL;
    }
    mutex->unlock();
    std::cout << "Server on " << client->getIp() << " for client no : " << client->getId() << " disconnected!" << std::endl;
}

void
BabelClient::onReceive(ISocket *client)
{
    Packet  *packet;

    //get packet
    if ((packet = client->readPacket(0)) != NULL) {
        //but first, let me take a RSA
        Rsa *rsa;
        if ((rsa = client->getSendRsa()) == NULL) {
            if (!packet->isEncrypted() && packet->getType() == Packet::SSLPublicKey)
                client->attachRsa(packet->unpack<Rsa>());
        }
        else if (packet->isEncrypted()) {

            if (packet->getType() == Packet::Id)
                BabelClient::executeIdentity(packet->unpack<Identity>(rsa), client);
            else if (packet->getType() == Packet::Inst)
                BabelClient::executeInstruction(packet->unpack<Instruct>(rsa), client);
        }
        else if (packet->getType() == Packet::String) {

            std::string *msg = packet->unpack<std::string>(rsa);
            std::cout << "Received message from " << client->getIp() << " (msg_length : " << msg->size() << ") : ";
            std::cout << *msg << std::endl;
            delete msg;
        }

        delete packet;
    }
}

