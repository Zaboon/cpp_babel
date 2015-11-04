#ifndef CPP_BABEL_WINSOCKET_H_
# define CPP_BABEL_WINSOCKET_H_

# include					<socketapi.h>
# include					<WinSock2.h>
# include					<WS2tcpip.h>
# include					"../ISocket.h"

class WinSocket :			public ISocket
{
private:
	WSADATA					_wsaData;
	SOCKET					_socket;
	struct addrinfo			*_addrinfo;

	const std::string		&getMachineIp()
	{
		static std::string ip = "";

		if (ip.size() == 0) {
			if (WSAStartup(MAKEWORD(2, 2), &this->_wsaData) == 0)
				throw "WSAStartup failed";
			char szHostName[255];
			gethostname(szHostName, 255);
			struct hostent *host_entry;
			host_entry = gethostbyname(szHostName);
			ip = inet_ntoa(*(struct in_addr *)*host_entry->h_addr_list);
			WSACleanup();
		}
		return (const_cast<const std::string &>(ip));
	}

	WinSocket(ISocket::Type type) : ISocket(type)
	{}

	/*
	** Warning => In a multithreaded environment, WSACleanup() terminates Windows Sockets operations for all threads
	*/
	WinSocket(const std::string &ip, int port, const std::string &proto) : ISocket(ISocket::Client, ip, port)
	{
		struct protoent		*pe;
		struct addrinfo		hints;

		if (WSAStartup(MAKEWORD(2, 2), &this->_wsaData) != 0)
			throw "WSAStartup failed";
		this->_socket = INVALID_SOCKET;
		this->_status = ISocket::Status::Waiting;
		this->_addrinfo = NULL;
		if ((pe = getprotobyname(proto.c_str())) == NULL)
			throw "getprotobyname failed";

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = pe->p_proto;

		if (getaddrinfo(ip.c_str(), std::to_string(port).c_str(), &hints, &this->_addrinfo) != 0)
		{
			WSACleanup();
			throw "getaddrinfo failed";
		}
		
		this->_socket = socket(this->_addrinfo->ai_family, this->_addrinfo->ai_socktype, this->_addrinfo->ai_protocol);
		if (this->_socket == INVALID_SOCKET)
		{
			freeaddrinfo(this->_addrinfo);
			WSACleanup();
			throw "Error at socket(): " + WSAGetLastError();
		}
		this->_status = ISocket::Status::Ready;
	}

	void					cancel()
	{
		if (this->_socket != INVALID_SOCKET)
		{
			closesocket(this->_socket);
			this->_socket = INVALID_SOCKET;
			this->_status = ISocket::Status::Canceled;
		}
	}

	int						start()
	{
		if (this->_status != ISocket::Status::Ready)
			return (0);
		if (this->_type == ISocket::Type::Server)
		{

		}
		else if (this->_type == ISocket::Type::Client)
		{
			if (connect(this->_socket, this->_addrinfo->ai_addr, static_cast<int>(this->_addrinfo->ai_addrlen)) == SOCKET_ERROR)
			{
				this->cancel();
				return (-1);
			}
		}
		return (1);
	}
};

#endif /* !CPP_BABEL_WINSOCKET_H_ */