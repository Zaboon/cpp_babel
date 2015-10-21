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

	virtual bool		sendWindows() {


	}

	virtual bool		receveWindows() {

	}
};