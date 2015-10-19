#pragma once

#include		"ISocket.h"

#include		<iostream>
#include		<string>
#include		<Windows.h>
#include		<sys/types.h>
#include		<io.h>
#include		<cstring>
#include		<vector>
#include		<winsock2.h>
#pragma			comment(lib, "ws2_32.lib")

class socketW : public ISocket {

private:
	SOCKET u_sock;

public:
	socketW() : ISocket() {
		WSADATA WSAData;
		WORD mkword = MAKEWORD(2, 2);
		int what = WSAStartup(mkword, &WSAData);
		
		if (what != 0) {
			std::cout << "This version is not supported ! - \n" << WSAGetLastError() << std::endl;
			throw std::runtime_error("problem with WSAStartup function");
		}
		else {
			std::cout << "Good - Everything fine !\n" << std::endl;
		}

		if ((u_sock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
			std::cout << "Probleme with socket function ! - \n" << WSAGetLastError() << std::endl;
			WSACleanup();
			throw std::runtime_error("problem with socket function");
		}
	}

	socketW(int fd) {
		u_sock = fd;
	}

	~socketW() {
		::_close(u_sock);
	}

	virtual bool			WBind() {
		struct sockaddr_in	sin;

		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = INADDR_ANY;
		sin.sin_port = htons(PORT);
		if (::bind(u_sock, (SOCKADDR *)(&sin), sizeof(sin)) == -1) {
			std::cout << "Something is wrong with bin, failed : " << WSAGetLastError() << std::endl;
			if ((closesocket(u_sock)) == SOCKET_ERROR) {
				std::cout << "Impossible to close socket : " << WSAGetLastError();
			}
			throw std::runtime_error("failed in WBind");
			return (false);
		}
		return (true);
	}

	virtual ISocket		*WAccept() {
		SOCKET			nSock;
		ISocket			*csock;
		SOCKADDR_IN		cin;
		int				size;

		if ((nSock = ::accept(u_sock, (SOCKADDR *)&cin, &size)) == INVALID_SOCKET) {
			std::cout << "Something is wrong with accept, failed : " << WSAGetLastError() << std::endl;
			WSACleanup();
			throw std::runtime_error("failed in WBind");
			return (NULL);
		}
		csock = new socketW(nSock);
		return (csock);
	}

	virtual bool		sendWindows() {


	}

	virtual bool		receveWindows() {

	}
};