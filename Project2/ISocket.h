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
	ISocket(Type type);

	ISocket(Type type, const std::string &ip, int port);

	virtual ~ISocket() {};

	//static
	static ISocket *getClient(const std::string &ip, int port = 4242, const std::string &proto = "TCP");

	//static
	static ISocket *getServer(int port = 4242, const std::string &proto = "TCP", bool _new = false);

	virtual int start() = 0;

	virtual void cancel() = 0;

	std::vector<ISocket *> getActiveClients();

	void addNewClient(ISocket *newClient);

	std::vector<unsigned char> read(unsigned int bytes);

	void write(const std::vector<unsigned char> &data, unsigned int id = 0);

	std::vector<unsigned char> operator<<(ISocket *client);

	void operator>>(const std::vector<unsigned char> &data);

	Type getType() const;

	Status getStatus() const;

	const std::string &getIp() const;

	void setIp(const std::string &ip);

	unsigned int getId() const;

	int  getPort() const;

	void attachOnConnect(EventHandler onConnect);

	void attachOnReceive(EventHandler onReceive);

	void attachOnDisconnect(EventHandler onDisconnect);

	EventHandler getOnConnect() const;

	EventHandler getOnReceive() const;

	EventHandler getOnDisconnect() const;

protected:

	unsigned int 			_id;
	Type					_type;
	Status 					_status;
	std::string 			_ip;
	int 					_port;

	std::vector<ISocket *>	_targets;

	EventHandler 			_onConnect;
	EventHandler 			_onReceive;
	EventHandler 			_onDisconnect;

	std::vector<unsigned char> _read_buffer;
	std::vector<unsigned char> _write_buffer;

};