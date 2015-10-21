//
// Created by rustam_t on 10/6/15.
//

#ifndef PROJECT2_MUTEXVAULT_HPP
#define PROJECT2_MUTEXVAULT_HPP

#include <vector>
#include <map>
#include <string>
#include "IMutex.hpp"

class MutexVault
{
public:

    static const unsigned long int bad_ptr;

    virtual ~MutexVault();

    template <typename T>
    static std::string SomethingToString(T something);

    static MutexVault *getMutexVault();

    static bool isBadPtr(void *ptr);

    IMutex *&operator[](unsigned int index);

    IMutex *&operator[](const std::string &index);

    void push_back(IMutex *new_element);

    void remove(unsigned int index);

protected:

    MutexVault();

    std::vector<IMutex *> _mutex_vault;
    std::map<std::string, IMutex *> _mutex_vault_map;
};

#endif //PROJECT2_MUTEXVAULT_HPP
