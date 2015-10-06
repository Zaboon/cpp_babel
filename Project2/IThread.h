#pragma once
#include <iostream>
#include <string>
#include <vector>

class IThread
{
public:

	enum Status
	{
		Ready,
		Running,
		Paused,
		Stopped
	};

	IThread(void *(*func_ptr)(void *))
	{
		this->_func_ptr = func_ptr;
	}

	virtual ~IThread()
	{
	}

	virtual bool start() const = 0;

	virtual bool stop() const = 0;

	virtual bool pause() const = 0;

	virtual void *operator()(void *) const = 0;

	Status getStatus()
	{
		return (this->_status);
	}

protected:

	void *(*_func_ptr)(void *);

	Status _status;
	
};

