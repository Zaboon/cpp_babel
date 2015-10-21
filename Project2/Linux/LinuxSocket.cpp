//
// Created by rustam_t on 10/19/15.
//

#include "LinuxSocket.h"

const std::string &
LinuxSocket::getMachineIp() const
{
    static std::string ip = "";

    if (ip.size() == 0) {

        char buffer[128];
        FILE *pipe = popen("hostname -i", "r");

        if (pipe) {
            if (fgets(buffer, 128, pipe) != NULL)
                ip += buffer;
            pclose(pipe);
            //erase whitespace and \n
            ip.erase(std::remove(ip.begin(), ip.end(), '\n'), ip.end());
            ip.erase(std::remove(ip.begin(), ip.end(), ' '), ip.end());
        }
    }

    return (const_cast<const std::string &>(ip));
}

void
LinuxSocket::acceptNewClients(unsigned int thread_id, LinuxSocket *server)
{
    struct sockaddr_in    s_in;
    socklen_t clinen = sizeof(s_in);
    LinuxSocket *newclient;

    server->_status = ISocket::Running;
    while (42)
    {
        newclient = new LinuxSocket(LinuxSocket::Client);
        if ((newclient->_socket = accept(server->_socket, reinterpret_cast<const struct sockaddr *>(&s_in), &clinen)) != 0) {

            server->_status = ISocket::Canceled;
            return;
        }
        newclient->_status = ISocket::Ready;
        newclient->_port = s_in.sin_port;
        newclient->_ip = inet_ntoa(s_in.sin_addr);
        server->addNewClient(newclient);
        newclient->_thread = new LinuxThread<void, LinuxSocket *>(LinuxSocket::launchClient);
        (*newclient->_thread)(newclient);
    }
}

void
LinuxSocket::launchClient(unsigned int thread_id, LinuxSocket *client)
{
    struct pollfd ufd[2];
    int rv;
    ssize_t send_val;
    ssize_t read_val;

    MutexVault *vault = MutexVault::getMutexVault();

    ufd[0].fd = (ufd[1].fd = client->_socket);
    ufd[0].events = POLLIN;
    ufd[1].events = POLLOUT;

    while (42)
    {
        if ((rv = poll(&ufd[0], 1, TIMEOUT)) == -1)
        {
            client->_status = ISocket::Canceled;
            return;
        }
        if (rv > 0)
        {
            //begin protected action
            (*vault)["readThread" + MutexVault::SomethingToString<unsigned int>(thread_id)]->lock(true);
            if (client->_read_buffer.size() > MAX_BUFFER_SIZE)
                client->_read_buffer.clear();
            client->_read_buffer.reserve(client->_read_buffer.size() + READ_HEAP);
            if ((read_val = recv(client->_socket, &client->_read_buffer[client->_read_buffer.size()], READ_HEAP, 0)) == -1)
                throw "Recv failed";
            client->_read_buffer.reserve(client->_read_buffer.size() + read_val);
            (*vault)["readThread" + MutexVault::SomethingToString<unsigned int>(thread_id)]->unlock();
            //end protected action
        }
        else if (!client->_write_buffer.empty())
        {
            if ((rv = poll(&ufd[1], 1, TIMEOUT)) == -1)
            {
                client->_status = ISocket::Canceled;
                return;
            }
            if (rv != 0)
            {
                //begin protected action
                (*vault)["writeThread" + MutexVault::SomethingToString<unsigned int>(thread_id)]->lock(true);
                if ((send_val = send(client->_socket, &(client->_write_buffer[0]), client->_write_buffer.size(), 0)) == -1)
                    throw "Send failed";
                //delete sent data
                client->_write_buffer.erase(client->_write_buffer.begin(), client->_write_buffer.begin() + send_val);
                (*vault)["writeThread" + MutexVault::SomethingToString<unsigned int>(thread_id)]->unlock();
                //end protected action
            }
            //no event
        }
    }
}

//dummy
LinuxSocket::LinuxSocket(LinuxSocket::Type type) : ISocket(type)
{
}

//Server
LinuxSocket::LinuxSocket(int port = 42, const std::string &proto) : ISocket(ISocket::Server, LinuxSocket::getMachineIp(), port)
{
    struct protoent       *pe;
    struct sockaddr_in    s_in;

    if (this->_ip.empty())
        throw "No ip detected!";
    this->_status = ISocket::Waiting;
    if ((pe = getprotobyname(proto.c_str())) == NULL)
        throw "getprotobyname failed";
    if ((this->_socket = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
        throw "socket failed";
    this->_status = ISocket::Ready;
    s_in.sin_family = AF_INET;
    s_in.sin_port = htons(reinterpret_cast<uint16_t>(port));
    s_in.sin_addr.s_addr = INADDR_ANY;
    if (bind(this->_socket, reinterpret_cast<const struct sockaddr *>(&s_in), sizeof(s_in)) == -1)
        throw "bind failed";
    if (listen(this->_socket, MAX_CLIENTS) == -1)
        throw "listen failed";

    //launch the thread to accept new connections
    this->_thread = new LinuxThread<void, LinuxSocket *>(LinuxSocket::acceptNewClients);
    (*this->_thread)(this);
}

//Client
LinuxSocket::LinuxSocket(const std::string &ip, int port = 42, const std::string &proto = "TCP") : ISocket(ISocket::Client, ip, port)
{

}