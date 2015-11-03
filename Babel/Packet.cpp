#include "Packet.h"
#include <iostream>

//real constructor
Packet::Packet()
{
}

//pbject specific constructors
Packet::Packet(std::string &str) : _type(Packet::String)
{
    for (unsigned int i = 0; i < str.size(); i++)
        this->_data.push_back(static_cast<unsigned char>(str[i]));
}

Packet::Packet(std::vector<int> &vec) : _type(Packet::IntVector)
{
    unsigned char *ptr;

    for (unsigned int i = 0; i < vec.size(); i++)
    {
        ptr = reinterpret_cast<unsigned char *>(vec[i]);
        for (unsigned int j = 0; j < sizeof(int); j++)
            this->_data.push_back(*ptr);
    }
}

//static
unsigned int
Packet::getHeaderSize()
{
    static unsigned int size = 0;

    if (size == 0)
        size = sizeof(unsigned int) * 3;
    return (size);
}

//get packet from bytestream (bytestream is then consumed)
Packet *
Packet::fromStream(std::vector<unsigned char> &data)
{
    unsigned int headerSize = Packet::getHeaderSize();
    if (data.size() <= headerSize)
        return (NULL);

    unsigned int *r_magic = reinterpret_cast<unsigned int *>(&data[0]);
    Packet::Type *r_type = reinterpret_cast<Packet::Type *>(&data[headerSize / 3]);
    unsigned int *r_size = reinterpret_cast<unsigned int *>(&data[headerSize / 3 * 2]);

    if (*r_magic != _MAGIC_ || *r_size + headerSize < data.size())
        return (NULL);
    Packet *newPacket = new Packet;
    newPacket->_type = *r_type;
    for (unsigned int i = 0; i < *r_size; i++) {
        newPacket->_data.push_back(data[i + headerSize]);
    }

    //consume flux
    data.erase(data.begin(), data.begin() + headerSize + *r_size);
    return (newPacket);
}

//get bytestream from packet
std::vector<unsigned char> *
Packet::build()
{
    unsigned char *magic_ptr;
    unsigned char *size_ptr;
    unsigned char *type_ptr;

    unsigned int magic = _MAGIC_;
    unsigned int length = static_cast<unsigned int>(this->_data.size());

    magic_ptr = reinterpret_cast<unsigned char *>(&magic);
    size_ptr = reinterpret_cast<unsigned char *>(&length);
    type_ptr = reinterpret_cast<unsigned char *>(&this->_type);

    //allocate
    std::vector<unsigned char> *build = new std::vector<unsigned char>(Packet::getHeaderSize());
    for (unsigned int i = 0; i < Packet::getHeaderSize() / 3; i++) {

        //magic goes first
        (*build)[i] = magic_ptr[i];
        //type
        (*build)[i + Packet::getHeaderSize() / 3] = type_ptr[i];
        //and finally size!
        (*build)[i + Packet::getHeaderSize() / 3 * 2] = size_ptr[i];
    }
    build->insert(build->end(), this->_data.begin(), this->_data.end());
    return (build);
}

std::vector<unsigned char> const &
Packet::getData() const
{
    return (this->_data);
}

Packet::Type
Packet::getType() const
{
    return (_type);
}

std::string *
Packet::getString()
{
    std::string *tmp = NULL;

    if (this->_type == Packet::String)
    {

        tmp = new std::string;
        for (unsigned int i = 0; i < this->_data.size(); i++)
            tmp->push_back(static_cast<char>(this->_data[i]));
    }
    return (tmp);
}

std::vector<int> *
Packet::getIntVector()
{
    std::vector<int> *tmp = NULL;
    int *ptr;

    if (this->_type == Packet::IntVector && this->_data.size() % sizeof(int) == 0)
    {
        tmp = new std::vector<int>();
        for (unsigned int i = 0; i < this->_data.size(); i += sizeof(int))
        {
            ptr = reinterpret_cast<int *>(&(this->_data[i]));
            tmp->push_back(*ptr);
        }
    }
    return (tmp);
}