#pragma once

#include <iostream>
#include <string>
#include <vector>

class ISocket
{
public:

	//dummy
	ISocket(Type type) : _type(type) {};

	ISocket(Type type, const std::string &ip, int port) : _type(type), _ip(ip), _port(port) {};

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

	virtual ~ISocket() {};

	//static
	static ISocket *getClient(const std::string &ip, int port = 42, const std::string &proto = "TCP")
	{

	};

	//static
	static ISocket *getServer(int port = 42, const std::string &proto = "TCP")
	{

	};

	virtual const std::vector<unsigned char> read(int id = 0) const = 0;

	virtual const float write(const std::vector<unsigned char> &data, int id = 0) const = 0;

	void addNewClient(ISocket *newClient)
	{
		if (this->getType() != Server)
			return;

		IMutex *_targetList = (*MutexVault::getMutexVault())["serverTargets"];
		_targetList->lock(true);
		this->_targets.push_back(newClient);
		_targetList->unlock();
	}

	const Type getType()
	{
		return (this->_type);
	};

	const Status getStatus()
	{
		return (this->_status);
	}

	virtual std::vector<unsigned char> operator<<(ISocket *client)
	{
		return (client->read());
	}

	virtual float operator>>(const std::vector<unsigned char> &data)
	{
		return (this->write(data));
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

protected:

	Type					_type;
	Status 					_status;
	std::string 			_ip;
	int 					_port;

	std::vector<ISocket *>	_targets;

	std::vector<unsigned char> _read_buffer;
	std::vector<unsigned char> _write_buffer;

};