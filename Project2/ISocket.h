#pragma once

#include		<iostream>
#include		<string>
#include		<Windows.h>
#include		<cstring>
#include		<vector>
#include		<winsock2.h>
#pragma			comment(lib, "ws2_32.lib")

#define			PORT	42

class ISocket
{
public:

	enum Type
	{
		Server,
		Client
	};

	virtual ~ISocket() {};

	//static
	virtual ISocket			*getClient(const std::string &Ip, int port = 42, const std::string &proto = "tcp") const = 0;

	//static
	virtual ISocket			*getServer(int port = 42, const std::string &proto = "tcp") const = 0;

	virtual const			std::string &read(int id = 0) const = 0;

	virtual const float		write(const std::string &data, int id = 0) const = 0;

	virtual bool			WBind() = 0;

	virtual bool			WListen() = 0;

	virtual ISocket			*WAccept() = 0;

	virtual bool			WClose() = 0;

	virtual const Type getType()
	{
		return this->_type;
	};

	virtual const std::string &operator<<(ISocket *client)
	{
		return (client->read());
	}

	virtual float operator>>(const std::string &data)
	{
		return (this->write(data));
	}

protected:

	ISocket()
	{
	}

	Type					_type;

	ISocket					*_main_target = NULL;
	std::vector<ISocket *>	_targets;

	std::string				_read_buffer;
	std::string				_write_buffer;

};