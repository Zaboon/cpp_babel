//
// Created by rustam_t on 11/11/15.
//

#ifndef CPP_BABEL_BABELCLIENT_HPP
#define CPP_BABEL_BABELCLIENT_HPP

#include "ISocket.h"
#include "MutexVault.hpp"
#include "Packet.h"
#include "Rsa.h"
#include "Identity.hpp"
#include "Sound/SoundManager.hpp"
#include "IThread.hpp"
#include <vector>

class BabelClient {

public:
    static BabelClient *getInstance();

    ~BabelClient()
    {
        for (unsigned int i = 0; i < this->_contacts.size(); i++)
        {
            if (this->_contacts[i] != NULL)
                delete this->_contacts[i];
        }
        if (this->_peer != NULL)
            delete this->_peer;
    }

    std::vector<Identity> getContacts();

    static void sendSound(unsigned int thread_id, ISocket *client);
    static void receiveSound(ISocket *client);
    static SoundManager *getSound();
    bool enterUsername(const std::string &username, ISocket *server);

    void addContact(Identity *id);
    void removeContact(Identity *id);

    void setConnected(bool status);
    bool isConnected() const;

    static bool answer(ISocket *client);
    bool call(const std::string &peername, ISocket *server);

    static void executeIdentity(Identity *, ISocket *client);

    static void executeInstruction(Instruct *, ISocket *client);

    static void onConnect(ISocket *client);

    static void onReceiveNotLogged(ISocket *client);
    static void waitingForUsernameValidation(ISocket *client);
    static void onReceiveLogged(ISocket *client);
    static void waitingForAnswer(ISocket *client);

    static void onDisconnect(ISocket *client);

private:

    BabelClient() : asked_call(false), _peer(NULL) {};

    bool connected;
    bool asked_call;
    std::vector<Identity *> _contacts;
    ISocket *_peer;
    IThread<void, ISocket*> *_peerthread;
};


#endif //CPP_BABEL_BABELCLIENT_HPP
