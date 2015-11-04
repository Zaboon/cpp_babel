//
// Created by rustam_t on 10/13/15.
//

#ifndef CPP_BABEL_PACKET_H
#define CPP_BABEL_PACKET_H

#include <string>
#include <vector>
#include <typeinfo>
#include "Rsa.h"

#define _MAGIC_ 0x0101010

class Packet
{
public:

    enum Type {

        String = 0xb16b00b5,
        IntVector = 0x42424242,
        SSLPublicKey = 0x4ab2321a
    };

    //object specific constructors
    Packet(std::string &str);
    Packet(std::vector<int> &vec);
    Packet(Rsa &);

    template <typename T>
    static Packet *pack(T &obj)
    {
        return (new Packet(obj));
    };

    //build a bytestream from the packet
    std::vector<unsigned char>              *build(Rsa *rsa = NULL);

    //reconstruct the packet from vector stream which will be consumed if succeeded
    static Packet                           *fromStream(std::vector<unsigned char> &data, Rsa *rsa = NULL);

    //unpack the packet to get your object back
    template <typename T>
    T *unpack()
    {
        if (typeid(T) == typeid(std::string))
            return (reinterpret_cast<T *>(this->getString()));
        else if (typeid(T) == typeid(std::vector<int>))
            return (reinterpret_cast<T *>(this->getIntVector()));
        else if (typeid(T) == typeid(Rsa))
            return (reinterpret_cast<T *>(this->getRsa()));
        return (NULL);
    };

    //just 3 * (sizeof(unsigned int))
    static unsigned int                     getHeaderSize();

    Type                                    getType() const;

    bool                                    isEncrypted() const;

    std::vector<unsigned char> const        &getData() const;

protected:

    //properties
    Type _type;
    bool _encrypted;
    std::vector<unsigned char> _data;

    //constructor
    Packet();

    virtual ~Packet() {};

    //object getters
    std::string *getString();
    std::vector<int> *getIntVector();
    Rsa *getRsa();
};

#endif //CPP_BABEL_PACKET_H
