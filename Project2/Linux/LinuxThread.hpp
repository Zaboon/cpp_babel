//
// Created by rustam_t on 10/6/15.
//

#ifndef PROJECT2_LINUXTHREAD_H
#define PROJECT2_LINUXTHREAD_H

#include <pthread.h>
#include <exception>
#include "../IThread.hpp"

template<typename T, typename U>
class LinuxThread : public IThread<T,U>
{
public:

    LinuxThread(T (*func_ptr)(U)) : IThread(func_ptr)
    {
    }

    virtual ~LinuxThread() {};

    //overloaded
    virtual void operator()(U param)
    {
        this->_param = param;

        if (pthread_create(&this->_thread, NULL, IThread::entry_point, static_cast<void *>(this)) != 0)
            throw new std::exception("Failed to create a new thread!");
        return;
    }

    virtual bool stop()
    {
        if (this->getStatus() == IThread<T, U>::Stopped ||
            this->getStatus() == IThread<T, U>::Ready)
            return (false);

        this->setStatus(IThread<T, U>::Stopped);
        return (pthread_cancel(this->_thread) == 0);
    }

protected:

    pthread_t _thread;

};


#endif //PROJECT2_LINUXTHREAD_H
