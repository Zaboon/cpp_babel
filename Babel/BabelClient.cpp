//
// Created by rustam_t on 11/11/15.
//

#include "BabelClient.hpp"
#include <unistd.h>

BabelClient *
BabelClient::getInstance()
{
    static BabelClient *_this;

    if (_this == NULL) {
        _this = new BabelClient;
        _this->connected = false;
    }
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
BabelClient::setConnected(bool status)
{
    this->connected = status;
}

void
BabelClient::addContact(Identity *id)
{
    IMutex *mutex = (*MutexVault::getMutexVault())["contacts"];

    mutex->lock(true);
    std::cout << "new contact : " << id->getUsername() << std::endl;
    this->_contacts.push_back(id);
    mutex->unlock();
}

void
BabelClient::removeContact(Identity *id)
{
    IMutex *mutex = (*MutexVault::getMutexVault())["contacts"];

    mutex->lock(true);
    std::cout << "remove contact : " << id->getUsername() << std::endl;
    for (unsigned int i = 0; i < this->_contacts.size(); i++)
        if (this->_contacts[i] == id)
        {
            delete this->_contacts[i];
            this->_contacts[i] = NULL;
            break;
        }
    mutex->unlock();
}

bool
BabelClient::answer(ISocket *client)
{
    BabelClient *_this = BabelClient::getInstance();
    IMutex *mutex = (*MutexVault::getMutexVault())["peer"];

    mutex->lock(true);
    if (_this->_peer != NULL && _this->_peer->getStatus() == ISocket::Ready)
    {
        //attach handlers
        if (_this->_peer->start() == -1) {
            std::cout << "Connection failed" << std::endl;
            client->writePacket(new Packet(ENDCALL));
            delete _this->_peer;
            _this->_peer = NULL;
        }
        else
        {
            //send ok!
            client->writePacket(new Packet(CALLESTABLISHED));
            mutex->unlock();
            return (true);
        }
    }
    mutex->unlock();
    return (false);
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
            _this->addContact(id);
            return; //no delete
        case (DELCONTACT) :
            _this->removeContact(id);
            break;
        case (ASKCALL) :
            mutex = (*MutexVault::getMutexVault())["peer"];
            mutex->lock(true);
            if (id->hasAdressAndName() && _this->_peer == NULL)
                _this->_peer = ISocket::getClient(id->getIp(), id->getPort());
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
BabelClient::waitingForUsernameValidation(ISocket *client)
{
    Packet *packet;
    Instruct *instruct;

    if ((packet = client->readPacket()) != NULL) {

        if (packet->getType() == Packet::Inst &&
            (instruct = packet->unpack<Instruct>()) != NULL) {

            if (*instruct == OK) {
                std::cout << "Successfully logged in!" << std::endl;
                BabelClient::getInstance()->setConnected(true);
                client->attachOnReceive(BabelClient::onReceive);
            }
            else {
                std::cout << "Failed to log in!" << std::endl;
                std::cout << "Try username caca" << std::endl;
                Identity i("caca", "127.0.0.1", 4242, CONNECTION);
                client->writePacket(new Packet(i));
            }
            delete instruct;
        }
        delete packet;
        return;
    }
}

void
BabelClient::inputUsername(ISocket *client)
{
    client->attachOnReceive(BabelClient::waitingForUsernameValidation);
}

void
BabelClient::onReceive(ISocket *client)
{
    Packet  *packet;

    //get packet
    if ((packet = client->readPacket()) != NULL) {
        //but first, let me take a RSA
        Rsa *rsa;
        if ((rsa = client->getSendRsa()) == NULL) {

            if (packet->getType() == Packet::SSLPublicKey) {

                if (packet->isEncrypted())
                    client->attachRsa(packet->unpack<Rsa>(client->getRecvRsa()));
                else
                    client->attachRsa(packet->unpack<Rsa>());

                std::cout << "Ok for public key for " << client->getIp() << std::endl;

                std::cout << "Try username pipi" << std::endl;
                Identity i("pipi", "127.0.0.1", 4242, CONNECTION);
                client->writePacket(new Packet(i));
                //redirect for response
                client->attachOnReceive(BabelClient::waitingForUsernameValidation);
            }
        }
        else if (packet->getType() == Packet::String) {

            std::string *msg = packet->unpack<std::string>();
            std::cout << "Received message from " << client->getIp() << " (msg_length : " << msg->size() << ") : ";
            std::cout << *msg << std::endl;
            delete msg;
        }
        else ;{

            if (packet->getType() == Packet::Id)
                BabelClient::executeIdentity(packet->unpack<Identity>(), client);
            else if (packet->getType() == Packet::Inst)
                BabelClient::executeInstruction(packet->unpack<Instruct>(), client);
        }


        delete packet;
    }
}

