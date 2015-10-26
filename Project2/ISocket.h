#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "MutexVault.hpp"

class ISocket
{
public:

	typedef void (*EventHandler)(ISocket *);

	enum Type
	{
		Server,
		Client
	};

	enum Status
	{
		Waiting,
		Ready,
		Running,
		Canceled
	};

	//dummy
	ISocket(Type type) : _type(type)
	{
		this->_onConnect = NULL;
		this->_onReceive = NULL;
	};

	ISocket(Type type, const std::string &ip, int port) : _type(type), _ip(ip), _port(port)
	{
		this->_onConnect = NULL;
		this->_onReceive = NULL;
	};

	virtual ~ISocket() {};

	//static
	static ISocket *getClient(const std::string &ip, int port = 42, const std::string &proto = "TCP")
	{
		return NULL;
	};

	//static
	static ISocket *getServer(int port = 42, const std::string &proto = "TCP")
	{
		return NULL;
	};

	virtual void startServer() = 0;

	void addNewClient(ISocket *newClient)
	{
		if (this->getType() != Server)
			return;

		//inherit events
		if (this->getOnConnect() != NULL)
			newClient->attachOnConnect(this->getOnConnect());
		if (this->getOnReceive() != NULL)
			newClient->attachOnReceive(this->getOnReceive());

		IMutex *_targetList = (*MutexVault::getMutexVault())["serverTargets"];
		_targetList->lock(true);
		this->_targets.push_back(newClient);
		newClient->_id = this->_targets.size();
		_targetList->unlock();
	}

	std::vector<unsigned char> read(unsigned int bytes)
	{
		IMutex *mutex;
		std::vector<unsigned char> tmp;

		if (MutexVault::isBadPtr((mutex = (*MutexVault::getMutexVault())["read" + MutexVault::somethingToString<unsigned int>(this->_id)])))
			return tmp;
		mutex->lock(true);
		if (bytes == 0)
		{
			std::cout << "buffer size " << this->_read_buffer.size() << std::endl;
			tmp.insert(tmp.end(), this->_read_buffer.begin(), this->_read_buffer.end());
			this->_read_buffer.clear();
		}
		else if (bytes <= this->_read_buffer.size())
		{
			for (unsigned int i = 0; i < bytes; i++)
				tmp.push_back(this->_read_buffer[i]);
			this->_read_buffer.erase(this->_read_buffer.begin(), this->_read_buffer.begin() + bytes);
		}
		mutex->unlock();
		return (tmp);
	}

	void write(const std::vector<unsigned char> &data, unsigned int id = 0)
	{
		IMutex *mutex;

		if (this->_type == Client)
		{
			if (MutexVault::isBadPtr((mutex = (*MutexVault::getMutexVault())["write" + MutexVault::somethingToString<unsigned int>(this->_id)])))
				return;
			mutex->lock(true);
			this->_write_buffer.insert(this->_write_buffer.end(), data.begin(), data.end());
			mutex->unlock();
		}
		else
		{
			if (MutexVault::isBadPtr((mutex = (*MutexVault::getMutexVault())["serverTargets"])))
				return;
			mutex->lock(true);
			if (id != 0 && id < this->_targets.size() && this->_targets[id - 1]->getStatus() == Running)
				this->_targets[id - 1]->write(data);
			else if (id == 0)
				for (unsigned int i = 0; i < this->_targets.size(); i++)
					this->_targets[i]->write(data);
			mutex->unlock();
		}
	}

	std::vector<unsigned char> operator<<(ISocket *client)
	{
		return (client->read(0));
	}

	void operator>>(const std::vector<unsigned char> &data)
	{
		return (this->write(data));
	}

	Type getType() const
	{
		return (this->_type);
	};

	Status getStatus() const
	{
		return (this->_status);
	}

	const std::string &getIp() const
	{
		return (this->_ip);
	}

	void setIp(const std::string &ip)
	{
		if (this->_type == Server)
			return;
		this->_ip = ip;
	}

	unsigned int getId() const
	{
		return (this->_id);
	}

	int  getPort() const
	{
		return (this->_port);
	}

	void attachOnConnect(EventHandler onConnect)
	{
		IMutex *mutex;

		if (MutexVault::isBadPtr((mutex = (*MutexVault::getMutexVault())["onConnect" + MutexVault::somethingToString<unsigned int>(this->_id)])))
			return;
		mutex->lock();
		this->_onConnect = onConnect;
		mutex->unlock();
	}

	void attachOnReceive(EventHandler onReceive)
	{
		IMutex *mutex;

		if (MutexVault::isBadPtr((mutex = (*MutexVault::getMutexVault())["onReceive" + MutexVault::somethingToString<unsigned int>(this->_id)])))
			return;
		mutex->lock();
		this->_onReceive = onReceive;
		mutex->unlock();
	}

	EventHandler getOnConnect() const
	{
		IMutex *mutex;
		EventHandler ret;

		if (MutexVault::isBadPtr((mutex = (*MutexVault::getMutexVault())["onConnect" + MutexVault::somethingToString<unsigned int>(this->_id)])))
			return NULL;
		mutex->lock();
		ret = this->_onConnect;
		mutex->unlock();
		return (ret);
	}

	EventHandler getOnReceive() const
	{
		IMutex *mutex;
		EventHandler ret;

		if (MutexVault::isBadPtr((mutex = (*MutexVault::getMutexVault())["onReceive" + MutexVault::somethingToString<unsigned int>(this->_id)])))
			return NULL;
		mutex->lock();
		ret = this->_onReceive;
		mutex->unlock();
		return (ret);
	}

protected:

	unsigned int 			_id;
	Type					_type;
	Status 					_status;
	std::string 			_ip;
	int 					_port;

	std::vector<ISocket *>	_targets;

	void 					(*_onConnect)(ISocket *);
	void 					(*_onReceive)(ISocket *);

	std::vector<unsigned char> _read_buffer;
	std::vector<unsigned char> _write_buffer;

};