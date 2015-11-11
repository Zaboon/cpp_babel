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
#include <utility>

#define TRY_LIMIT 10

class BabelServer {

public:

    ~BabelServer()
    {
        IMutex *mutex = (*MutexVault::getMutexVault())["people"];

        mutex->lock(true);
        for (unsigned int i = 0; i < this->_people.size(); i++)
        {
            if (this->_people[i] != NULL) {
                //delete this->_people[i]->first;
                delete this->_people[i]->second;
                delete this->_people[i];
            }
        }
        mutex->unlock();
    }

    typedef std::pair<ISocket *, Identity *> Profile;

    static BabelServer *getInstance(bool del = false);

    void    deleteProfile(Profile *to_delete);

    Profile *getByUsername(char *username);

    Profile *getByIdentity(Identity *id);

    Profile *getByClient(ISocket *client);

    void sendPacketToAllRegisteredUsers(Packet *p, ISocket *except = NULL);

    static void onDisconnect(ISocket *client);

    static void executeInstruction(Instruct *instruct, ISocket *client);

    static void executeIdentity(Identity *identity, ISocket *client);

    static void onReceive(ISocket *client);

    static void onConnect(ISocket *client);

private:

    BabelServer() {};

    std::vector<Profile *> _people;
    std::map<ISocket *, unsigned int> _tries;
};


#endif //CPP_BABEL_BABELSERVER_HPP
