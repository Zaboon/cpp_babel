//
// Created by rustam_t on 10/19/15.
//

#ifndef CPP_BABEL_LINUXSOCKET_H
#define CPP_BABEL_LINUXSOCKET_H

#include <algorithm>
#include <exception>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/poll.h>
#include "LinuxThread.hpp"
#include "../ISocket.h"

#define MAX_CLIENTS 42
#define TIMEOUT 5
#define READ_HEAP 4096
#define MAX_BUFFER_SIZE 21920

class LinuxSocket : public ISocket
{
private:

    int                                 _socket;
    LinuxThread<void, LinuxSocket *>    *_thread;

protected:

    //Client
    LinuxSocket(const std::string &ip, int port = 42, const std::string &proto = "TCP");

    static void acceptNewClients(unsigned int thread_id, LinuxSocket *server);

    static void launchClient(unsigned int thread_id, LinuxSocket *client);

public:

    //Server
    LinuxSocket(int port = 42, const std::string &proto = "TCP");

    //dummy
    LinuxSocket(Type type);

    static const std::string &getMachineIp();

    virtual void startServer();
};


#endif //CPP_BABEL_LINUXSOCKET_H
