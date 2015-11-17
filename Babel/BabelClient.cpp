//
// Created by rustam_t on 11/11/15.
//

#include "Linux/LinuxSocket.h"
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

bool
BabelClient::isConnected() const
{
    return (this->connected);
}

SoundManager *
BabelClient::getSound()
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


bool
BabelClient::enterUsername(const std::string &username, ISocket *server)
{
    Identity *id;

    if (!this->connected) {

        id = new Identity(username, LinuxSocket::getMachineIp(), 5555, CONNECTION);
        server->writePacket(Packet::pack<Identity>(*id));
        server->attachOnReceive(BabelClient::waitingForUsernameValidation);
        delete id;
        return (true);
    }
    return (false);
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

void
BabelClient::endPeer(ISocket *client)
{
    IMutex *mutex = (*MutexVault::getMutexVault())["peer"];
    BabelClient *_this = BabelClient::getInstance();

    mutex->lock(true);
    if (_this->_peer != NULL) {

        BabelClient::getSound()->stopStream();
        delete _this->_peerthread;
        _this->_peer->cancel();
        usleep(100);
        delete _this->_peer;
        _this->_peer = NULL;
    }
    mutex->unlock();
}

void
BabelClient::receiveSound(ISocket *client)
{
    Packet* packet;
    SoundPacket *sound;

    while ((packet = client->readPacket()) != NULL) {

        if ((sound = packet->unpack<SoundPacket>()) != NULL) {

            BabelClient::getSound()->setReceivedRetenc(sound->retenc);
            BabelClient::getSound()->setReceivedData(sound->data);
            delete sound;
        }
        delete packet;
    }
}

void
BabelClient::sendSound(unsigned int thread_id, ISocket *client)
{
    while (client->getStatus() != ISocket::Canceled) {
        client->writePacket(Packet::pack<SoundPacket>(*(getSound()->getStruct())));
    }
}

bool
BabelClient::call(const std::string &peername, ISocket *server)
{
    bool ret = false;
    Identity *id;
    IMutex *mutex = (*MutexVault::getMutexVault())["peer"];

    mutex->lock(true);
    if (this->_peer == NULL)
    {
        id = new Identity(peername, ASKCALL);
        server->writePacket(Packet::pack<Identity>(*id));
        server->attachOnReceive(BabelClient::waitingForAnswer);
        delete id;
        ret = true;
    }
    else
        std::cout << "You cannot call 2 persons at the same time!" << std::endl;
    mutex->unlock();
    return (ret);
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
            _this->_peer->cancel();
            usleep(100);
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
            std::cout << "asked to call " << id->getIp() << std::endl;
            if (id->hasAdressAndName() && _this->_peer == NULL) {

                _this->_peer = ISocket::getClient(id->getIp(), id->getPort());
                _this->_peer->attachOnReceive(BabelClient::receiveSound);
                _this->_peer->attachOnDisconnect(BabelClient::endPeer);
                usleep(100);
                if (_this->_peer->start() == -1) {
                    std::cout << "Failed to connect!" << std::endl;
                    delete _this->_peer;
                    _this->_peer = NULL;
                }
                else {
                    _this->getSound();

                    _this->_peerthread = new LinuxThread<void, ISocket *>(BabelClient::sendSound);
                    (*_this->_peerthread)(_this->_peer);
                }
            }
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
                delete _this->_peerthread;
                _this->getSound()->stopStream();
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
        BabelClient::getSound()->stopStream();
        usleep(100);
        delete _this->_peer;
        _this->_peer = NULL;
    }
    mutex->unlock();
    std::cout << "Server on " << client->getIp() << " for client no : " << client->getId() << " disconnected!" << std::endl;
}

void
BabelClient::waitingForAnswer(ISocket *client)
{
    Packet *packet;
    Instruct *instruct;
    Identity *id;
    BabelClient *_this = BabelClient::getInstance();

    std::cout << "Waiting for answer" << std::endl;
    if ((packet = client->readPacket()) != NULL) {

        if (packet->getType() == Packet::Inst &&
            (instruct = packet->unpack<Instruct>()) != NULL) {

            if (*instruct == KO) {
                std::cout << "No such user or whatever" << std::endl;
                client->attachOnReceive(BabelClient::onReceiveLogged);
            }
            delete instruct;
        }
        else if (packet->getType() == Packet::Id)
        {
            if ((id = packet->unpack<Identity>()) != NULL) {

                if (id->getInstruct() == OK) {
                    std::cout << "Creating server" << std::endl;

                    IMutex *mutex = (*MutexVault::getMutexVault())["peer"];
                    mutex->lock(true);
                    _this->_peer = ISocket::getServer(5555);
                    _this->_peer->attachOnReceive(BabelClient::receiveSound);
                    _this->getSound();
                    _this->_peer->start();

                    _this->_peerthread = new LinuxThread<void, ISocket *>(BabelClient::sendSound);
                    (*_this->_peerthread)(_this->_peer);

                    client->attachOnReceive(BabelClient::onReceiveLogged);
                    mutex->unlock();
                }
                delete id;
            }
        }
        delete packet;
    }
}

void
BabelClient::onReceiveLogged(ISocket *client) {

    Packet *packet;

    //get packet
    if ((packet = client->readPacket()) != NULL) {

        if (packet->getType() == Packet::Id)
            BabelClient::executeIdentity(packet->unpack<Identity>(), client);
        else if (packet->getType() == Packet::Inst)
            BabelClient::executeInstruction(packet->unpack<Instruct>(), client);
        else if (packet->getType() == Packet::String) {

            std::string *msg = packet->unpack<std::string>();
            std::cout << "Received message from " << client->getIp() << " (msg_length : " << msg->size() << ") : ";
            std::cout << *msg << std::endl;
            delete msg;
        }

        delete packet;
    }
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
                client->attachOnReceive(BabelClient::onReceiveLogged);
            }
            else
                std::cout << "Username invalid or already taken" << std::endl;
            delete instruct;
        }
        delete packet;
    }
}

void
BabelClient::onReceiveNotLogged(ISocket *client)
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
                std::cout << "Enter your username : " << std::endl;
                //wait for username answer
                client->attachOnReceive(BabelClient::waitingForUsernameValidation);
            }
        }
        delete packet;
    }
}

