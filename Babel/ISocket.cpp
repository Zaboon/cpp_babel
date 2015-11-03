#include "ISocket.h"
#include "Linux/LinuxSocket.h"
#include "Windows/WinSocket.h"

//dummy
ISocket::ISocket(Type type) : _type(type)
{
    this->_onConnect = NULL;
    this->_onReceive = NULL;
    this->_onDisconnect = NULL;
};

ISocket::ISocket(Type type, const std::string &ip, int port) : _type(type), _ip(ip), _port(port)
{
    this->_onConnect = NULL;
    this->_onReceive = NULL;
    this->_onDisconnect = NULL;
};

ISocket *
ISocket::getClient(const std::string &ip, int port, const std::string &proto)
{
    #ifdef _WIN_32
        return (new WinSocket(ip, port, proto));
    #else
        return (new LinuxSocket(ip, port, proto));
    #endif
};

ISocket *
ISocket::getServer(int port, const std::string &proto, bool _new)
{
    static ISocket *instance = NULL;

    if (_new || !instance) {

    #ifdef _WIN_32
        instance = new WinSocket(port, proto);
    #else
        instance = new LinuxSocket(port, proto);
    #endif
    }
    return (instance);
};

std::vector<ISocket *>
ISocket::getActiveClients()
{
    std::vector<ISocket *> tmp;
    IMutex *mutex;

    if (this->getType() == ISocket::Server)
    {
        mutex = (*MutexVault::getMutexVault())["serverTargets"];
        mutex->lock(true);
        for (unsigned int i = 0; i < this->_targets.size(); i++)
            if (this->_targets[i]->getStatus() == ISocket::Running)
                tmp.push_back(this->_targets[i]);
        mutex->unlock();
    }
    return tmp;
}
void
ISocket::addNewClient(ISocket *newClient)
{
    ISocket::EventHandler handler[3];
    if (this->getType() != ISocket::Server)
        return;

    //inherit events
    if ((handler[0] = this->getOnConnect()) != NULL)
        newClient->attachOnConnect(handler[0]);
    if ((handler[1] = this->getOnReceive()) != NULL)
        newClient->attachOnReceive(handler[1]);
    if ((handler[2] = this->getOnDisconnect()) != NULL)
        newClient->attachOnDisconnect(handler[2]);

    IMutex *_targetList = (*MutexVault::getMutexVault())["serverTargets"];
    _targetList->lock(true);
    this->_targets.push_back(newClient);
    newClient->_id = this->_targets.size();
    _targetList->unlock();
}

std::vector<unsigned char>
ISocket::read(unsigned int bytes)
{
    IMutex *mutex;
    std::vector<unsigned char> tmp;

    if (MutexVault::isBadPtr((mutex = (*MutexVault::getMutexVault())["read" + MutexVault::toString(this->_id)])))
        return tmp;
    mutex->lock(true);
    if (bytes == 0)
    {
        tmp.insert(tmp.end(), this->_read_buffer.begin(), this->_read_buffer.end());
        this->_read_buffer.clear();
    }
    else if (bytes <= this->_read_buffer.size())
    {
        for (unsigned int i = 0; i < bytes; i++)
            tmp.push_back(this->_read_buffer[i]);
        this->_read_buffer.erase(this->_read_buffer.begin(), this->_read_buffer.begin() + bytes);
    }
    mutex->unlock();
    return (tmp);
}

void
ISocket::write(const std::vector<unsigned char> &data, unsigned int id)
{
    IMutex *mutex;

    if (this->_type == ISocket::Client)
    {
        if (MutexVault::isBadPtr((mutex = (*MutexVault::getMutexVault())["write" + MutexVault::toString(this->_id)])))
            return;
        mutex->lock(true);
        this->_write_buffer.insert(this->_write_buffer.end(), data.begin(), data.end());
        mutex->unlock();
    }
    else
    {
        if (MutexVault::isBadPtr((mutex = (*MutexVault::getMutexVault())["serverTargets"])))
            return;
        mutex->lock(true);
        if (id != 0 && id < this->_targets.size() && this->_targets[id - 1]->getStatus() == ISocket::Running)
            this->_targets[id - 1]->write(data);
        else if (id == 0)
            for (unsigned int i = 0; i < this->_targets.size(); i++)
                this->_targets[i]->write(data);
        mutex->unlock();
    }
}

std::vector<unsigned char>
ISocket::operator<<(ISocket *client)
{
    return (client->read(0));
}

void
ISocket::operator>>(const std::vector<unsigned char> &data)
{
    return (this->write(data));
}

unsigned int
ISocket::getId() const
{
    return (this->_id);
}

const std::string &
ISocket::getIp() const
{
    return (this->_ip);
}

void
ISocket::setIp(const std::string &ip)
{
    if (this->_type == ISocket::Server || this->_status != ISocket::Waiting)
        return;
    this->_ip = ip;
}

int
ISocket::getPort() const
{
    return (this->_port);
}

ISocket::Type
ISocket::getType() const
{
    return (this->_type);
};

ISocket::Status
ISocket::getStatus() const
{
    return (this->_status);
}

void
ISocket::attachOnConnect(ISocket::EventHandler onConnect)
{
    IMutex *mutex;

    if (MutexVault::isBadPtr((mutex = (*MutexVault::getMutexVault())["onConnect" + MutexVault::toString<unsigned int>(this->_id)])))
        return;
    mutex->lock();
    this->_onConnect = onConnect;
    mutex->unlock();
}

void
ISocket::attachOnReceive(ISocket::EventHandler onReceive)
{
    IMutex *mutex;

    if (MutexVault::isBadPtr((mutex = (*MutexVault::getMutexVault())["onReceive" + MutexVault::toString<unsigned int>(this->_id)])))
        return;
    mutex->lock();
    this->_onReceive = onReceive;
    mutex->unlock();
}

void
ISocket::attachOnDisconnect(ISocket::EventHandler onDisconnect)
{
    IMutex *mutex;

    if (MutexVault::isBadPtr((mutex = (*MutexVault::getMutexVault())["onDisconnect" + MutexVault::toString<unsigned int>(this->_id)])))
        return;
    mutex->lock();
    this->_onDisconnect = onDisconnect;
    mutex->unlock();
}

ISocket::EventHandler
ISocket::getOnConnect() const
{
    IMutex *mutex;
    ISocket::EventHandler ret;

    if (MutexVault::isBadPtr((mutex = (*MutexVault::getMutexVault())["onConnect" + MutexVault::toString<unsigned int>(this->_id)])))
        return NULL;
    mutex->lock();
    ret = this->_onConnect;
    mutex->unlock();
    return (ret);
}

ISocket::EventHandler
ISocket::getOnReceive() const
{
    IMutex *mutex;
    ISocket::EventHandler ret;

    if (MutexVault::isBadPtr((mutex = (*MutexVault::getMutexVault())["onReceive" + MutexVault::toString<unsigned int>(this->_id)])))
        return NULL;
    mutex->lock();
    ret = this->_onReceive;
    mutex->unlock();
    return (ret);
}

ISocket::EventHandler
ISocket::getOnDisconnect() const
{
    IMutex *mutex;
    ISocket::EventHandler ret;

    if (MutexVault::isBadPtr((mutex = (*MutexVault::getMutexVault())["onDisconnect" + MutexVault::toString<unsigned int>(this->_id)])))
        return NULL;
    mutex->lock();
    ret = this->_onDisconnect;
    mutex->unlock();
    return (ret);
}