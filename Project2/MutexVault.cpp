#include <sstream>
#include "MutexVault.hpp"
#include "IMutex.hpp"
#include "Linux/LinuxMutex.hpp"

const unsigned long int MutexVault::bad_ptr = 0x00000004;

MutexVault::~MutexVault() {};

MutexVault::MutexVault() {};

MutexVault *
MutexVault::getMutexVault()
{
    static MutexVault *instance = NULL;

    if (instance == NULL)
        instance = new MutexVault();
    return (instance);
}

bool
MutexVault::isBadPtr(void *ptr)
{
    return (ptr == reinterpret_cast<void *>(MutexVault::bad_ptr));
}

IMutex *
MutexVault::operator[](unsigned int index)
{
    if (index >= this->_mutex_vault.size())
        return (reinterpret_cast<IMutex *>(MutexVault::bad_ptr));
    return (this->_mutex_vault[index]);
}

IMutex *
MutexVault::operator[](const std::string &index)
{
    if (this->_mutex_vault_map[index] == NULL)
        this->_mutex_vault_map[index] = new LinuxMutex();
    return (this->_mutex_vault_map[index]);
}

void
MutexVault::push_back(IMutex *new_element)
{
    this->_mutex_vault.push_back(new_element);
}

void
MutexVault::remove(unsigned int index)
{
    if (index < this->_mutex_vault.size() && this->_mutex_vault[index] != NULL)
    {
        delete this->_mutex_vault[index];
        this->_mutex_vault[index] = NULL;
    }
}

