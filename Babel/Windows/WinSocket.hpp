#ifndef CPP_BABEL_WINSOCKET_H_
# define CPP_BABEL_WINSOCKET_H_

# pragma comment(lib, "Ws2_32.lib")
# define _WINSOCK_DEPRECATED_NO_WARNINGS
# define MAX_CLIENTS				42

# include							<socketapi.h>
# include							<WinSock2.h>
# include							<WS2tcpip.h>
# include							"WinThread.hpp"
# include							"../BBException.hpp"
# include							"../ISocket.h"

/*
** Warning => WSACleanup() terminates Windows Sockets operations for all threads
*/
class WinSocket :					public ISocket
{
private:
	WSADATA							_wsaData;
	SOCKET							_socket;
	struct addrinfo					*_addrinfo;
	bool							_socketOpened;
	WinThread<void, WinSocket *>    *_thread;

	const std::string				&getMachineIp()
	{
		static std::string ip = "";

		if (ip.size() == 0) {
			if (WSAStartup(MAKEWORD(2, 2), &this->_wsaData) == 0)
				throw BBException("WSAStartup failed");
			char szHostName[255];
			gethostname(szHostName, 255);
			struct hostent *host_entry;
			host_entry = gethostbyname(szHostName);
			ip = inet_ntoa(*(struct in_addr *)*host_entry->h_addr_list);
			WSACleanup();
		}
		return (const_cast<const std::string &>(ip));
	}
	
	void							launchWSA()
	{
		if (WSAStartup(MAKEWORD(2, 2), &this->_wsaData) != 0)
			throw BBException("WSAStartup failed");
		this->_socket = INVALID_SOCKET;
		this->_status = ISocket::Status::Waiting;
		this->_addrinfo = NULL;
	}

	void							acceptNewClients(unsigned int  thread_id, WinSocket *server)
	{
		WinSocket					*newClient;
		struct sockaddr_in			s_in;
		int							s_inLength = sizeof(s_in);

		server->_status = ISocket::Status::Running;
		while (server->_status == ISocket::Status::Running)
		{
			newClient = new WinSocket(ISocket::Type::Client);
			if ((newClient->_socket = accept(server->_socket, reinterpret_cast<struct sockaddr *>(&s_in), &s_inLength)) == INVALID_SOCKET)
			{
				closesocket(newClient->_socket);
				server->_status = ISocket::Status::Canceled;
			}
			else
			{
				newClient->_socketOpened = true;
				newClient->_status = ISocket::Ready;
				newClient->_port = s_in.sin_port;
				newClient->_ip = inet_ntoa(s_in.sin_addr);
				server->addNewClient(newClient);
				newClient->_thread = new WinThread<void, WinSocket *>(WinSocket::launchClient);
				(*newClient->_thread)(newClient);
			}
		}
	}

	void							launchClient(unsigned int thread_id, WinSocket *client)
	{
		// TO DO
	}

	// DUMMY
	WinSocket(ISocket::Type type):	ISocket(type)
	{
		this->_socketOpened = false;
	}

	// SERVER
	WinSocket(int port, const std::string &proto) : ISocket(ISocket::Server, WinSocket::getMachineIp(), port)
	{
		struct protoent				*pe;
		struct addrinfo				hints;

		if (this->_ip.empty())
			throw BBException("No ip detected!");
		if ((pe = getprotobyname(proto.c_str())) == NULL)
			throw BBException("getprotobyname failed");

		this->launchWSA();
		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET; // test with AF_UNSPEC later
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = pe->p_proto;
		hints.ai_flags = AI_PASSIVE;

		if (getaddrinfo(NULL, std::to_string(port).c_str(), &hints, &this->_addrinfo) != 0)
		{
			WSACleanup();
			throw BBException("getaddrinfo failed");
		}

		if ((this->_socket = socket(this->_addrinfo->ai_family, this->_addrinfo->ai_socktype, this->_addrinfo->ai_protocol)) == INVALID_SOCKET ||
			bind(this->_socket, this->_addrinfo->ai_addr, static_cast<int>(this->_addrinfo->ai_addrlen)) == SOCKET_ERROR ||
			listen(this->_socket, MAX_CLIENTS) == SOCKET_ERROR)
		{
			freeaddrinfo(this->_addrinfo);
			WSACleanup();
			throw BBException("Error on socket(), listen() or bind(): " + WSAGetLastError());
		}
		freeaddrinfo(this->_addrinfo); // no longer needed
		this->_status = ISocket::Status::Ready;
	}

	// CLIENT
	WinSocket(const std::string &ip, int port, const std::string &proto) : ISocket(ISocket::Client, ip, port)
	{
		struct protoent				*pe;
		struct addrinfo				hints;

		if ((pe = getprotobyname(proto.c_str())) == NULL)
			throw BBException("getprotobyname failed");

		this->launchWSA();
		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = pe->p_proto;

		if (getaddrinfo(ip.c_str(), std::to_string(port).c_str(), &hints, &this->_addrinfo) != 0)
		{
			WSACleanup();
			throw BBException("getaddrinfo failed");
		}
		
		this->_socket = socket(this->_addrinfo->ai_family, this->_addrinfo->ai_socktype, this->_addrinfo->ai_protocol);
		if (this->_socket == INVALID_SOCKET)
		{
			freeaddrinfo(this->_addrinfo);
			WSACleanup();
			throw BBException("Error at socket(): " + WSAGetLastError());
		}
		this->_status = ISocket::Status::Ready;
	}

	void							cancel()
	{
		IMutex						*mutex;
		
		mutex = (*MutexVault::getMutexVault())["close" + MutexVault::toString(this->_id)];
		
		if (this->_type == ISocket::Type::Server)
		{
			std::vector<ISocket *> activeClients = this->getActiveClients();
			std::cout << "disconnecting " << activeClients.size() << " clients" << std::endl;
			for (unsigned int i = 0; i < activeClients.size(); i++)
				activeClients[i]->cancel();
		}
		mutex->lock(true);
		if (this->_socket != INVALID_SOCKET)
			closesocket(this->_socket);
		this->_socket = INVALID_SOCKET;
		this->_socketOpened = false;
		mutex->unlock();
		this->_status = ISocket::Status::Canceled;
	}

	int								start()
	{
		if (this->_status != ISocket::Status::Ready)
			return (0);
		if (this->_type == ISocket::Type::Server)
		{
			this->_thread = new WinThread<void, WinSocket *>(WinSocket::acceptNewClients);
			(*this->_thread)(this);
		}
		else if (this->_type == ISocket::Type::Client)
		{
			if (connect(this->_socket, this->_addrinfo->ai_addr, static_cast<int>(this->_addrinfo->ai_addrlen)) == SOCKET_ERROR)
			{
				this->cancel();
				return (-1);
			}
			this->_thread = new WinThread<void, WinSocket *>(WinSocket::launchClient);
			(*this->_thread)(this);
		}
		return (1);
	}
};

#endif /* !CPP_BABEL_WINSOCKET_H_ */