#include "Packet.h"
#include <iostream>

int main()
{
    Packet *send;
    Packet *recv;
    std::vector<unsigned char> *stream;
    std::string *recvString;

    std::string sendString = "Hey! This is a test!";

    //or send = new Packet(sendString);
    send = Packet::pack<std::string>(sendString);
    //build the stream
    stream = send->build();

    //
    //send the stream here ->
    //

    std::cout << "Stream size before creating the packet : " << stream->size() << std::endl;
    //reinterpret the stream
    if ((recv = Packet::fromStream(*stream)) == NULL) {
        //error occured here
        return (-1);
    }
    std::cout << "Stream size after creating the packet : " << stream->size() << std::endl;
    if ((recvString = recv->unpack<std::string>()) == NULL) {
        //unpack or template error
        return (-1);
    }

    std::cout << "Packet contents : " << *recvString << std::endl;
    return (0);
}