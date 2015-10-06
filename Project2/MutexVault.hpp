//
// Created by rustam_t on 10/6/15.
//

#ifndef PROJECT2_MUTEXVAULT_HPP
#define PROJECT2_MUTEXVAULT_HPP

#include <vector>
#include "IMutex.hpp"

class MutexVault
{
public:

    static MutexVault *getMutexVault()
    {
        static MutexVault *instance = NULL;

        if (instance == NULL)
            instance = new MutexVault();
        return (instance);
    }

    virtual ~MutexVault() {};

    virtual IMutex *&operator[](unsigned int index)
    {
        static IMutex *useless = NULL;

        if (index >= this->_mutex_vault.size())
            return (useless);
        return (this->_mutex_vault[index]);
    }

    virtual void push_back(IMutex *new_element)
    {
        this->_mutex_vault.push_back(new_element);
    }

    virtual void remove(unsigned int index)
    {
        if (index < this->_mutex_vault.size() && this->_mutex_vault[index] != NULL)
        {
            delete this->_mutex_vault[index];
            this->_mutex_vault[index] = NULL;
        }
    }

protected:

    MutexVault() {};

    std::vector<IMutex *> _mutex_vault;
};

#endif //PROJECT2_MUTEXVAULT_HPP
