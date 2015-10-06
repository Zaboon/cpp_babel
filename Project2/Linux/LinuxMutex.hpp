//
// Created by rustam_t on 10/6/15.
//

#ifndef PROJECT2_LINUXMUTEX_HPP
#define PROJECT2_LINUXMUTEX_HPP

class LinuxMutex : public IMutex
{
public:

    virtual bool lock(bool wait = true)
    {
        if (this->getStatus() == IMutex::Unlocked || wait)
        {
            pthread_mutex_lock(&this->_mutex);
            return (true);
        }
    };

    virtual bool unlock()
    {
        if (this->getStatus() == IMutex::Locked)
            pthread_mutex_unlock(&this->_mutex);
        return (true);
    }

    ~LinuxMutex()
    {
        pthread_mutex_destroy(&this->_mutex);
    };

protected:

    pthread_mutex_t _mutex;
};

#endif //PROJECT2_LINUXMUTEX_HPP
