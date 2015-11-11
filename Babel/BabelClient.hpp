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

    void addContact(Identity *id);
    void removeContact(Identity *id);

    static void executeIdentity(Identity *, ISocket *client);

    static void executeInstruction(Instruct *, ISocket *client);

    static void onConnect(ISocket *client);

    static void onReceive(ISocket *client);

    static void onDisconnect(ISocket *client);

private:

    BabelClient() : asked_call(false), _peer(NULL) {};

    bool asked_call;
    Instruct *latest_cmd;
    std::vector<Identity *> _contacts;
    ISocket *_peer;
};


#endif //CPP_BABEL_BABELCLIENT_HPP
