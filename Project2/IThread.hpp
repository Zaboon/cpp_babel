#pragma once

#include <iostream>
#include <string>
#include <vector>

template<typename T, typename U>
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

	IThread(T (*func_ptr)(U))
	{
		this->_func_ptr = func_ptr;
		this->_status = Ready;
	}

	virtual ~IThread()
	{
	}

	Status getStatus() const
	{
		return (this->_status);
	}

	void setStatus(Status status)
	{
		this->_status = status;
	}

	virtual U getParameter() const
	{
		return (this->_param);
	}

	virtual void operator()(U param) = 0;

protected:

	static void *(entry_point)(void *_this)
	{
		IThread *self = dynamic_cast<IThread<T, U> *>(_this);

		self->setStatus(Running);
		self->_func_ptr(self->getParameter());
		self->setStatus(Stopped);
		return (NULL);
	}

	T (*_func_ptr)(U);

	U _param;

	Status _status;
	
};

