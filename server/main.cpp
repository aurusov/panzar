/*!
  \copyright (c) ���� ��� panzar, 2011
  \file      main.cpp
  \author    ������ ������ (drobus@gmail.com)
  \date      19.10.2011
  \brief     ���������� ������
  \indent    4T
*/

// ----------------------------------------------------------------------- INCLUDES
#include <iostream>
// ----------------------------------------------------------------------- SYNOPSIS
#include "utils/params.h"
#include "utils/socket.h"
// --------------------------------------------------------------------------------

void main(int argc, const char* argv[])
{
	ParamParser paramParser(argc, argv);

	std::string    ip    = "127.0.0.1";
	unsigned short port  = 1234;
	unsigned int   count = 10;

	if (!paramParser.get("ip",    ip   ) ||
	    !paramParser.get("port",  port ) ||
	    !paramParser.get("count", count))
	{
		std::cout << "use client.exe with params:" << std::endl
		          << "server.exe --ip=<server_address> --port=<server_port> --count=<clients_count>" << std::endl;
		return;
	}

	SocketInitializer socketInitializer;
	if (!socketInitializer.good())
	{
		std::cerr << "socket initialition error: " << WSAGetLastError() << std::endl;
		return;
	}

	Socket         socket;
	SocketMonicker socketMonicker(socket);
	if (!socket.create())
	{
		std::cerr << "socket creation error: " << WSAGetLastError() << std::endl;
		return;
	}

	if (!socket.bind(ip, port))
	{
		std::cerr << "socket connection error: " << WSAGetLastError() << std::endl;
		return;
	}

	if (!socket.listen(count))
	{
		std::cerr << "socket listen error: " << WSAGetLastError() << std::endl;
		return;
	}

	Socket         acceptSocket;
	SocketMonicker acceptSocketMonicker(acceptSocket);
	for (;;)
	{
		acceptSocket = Socket();
		while (!acceptSocket.good())
		{
			acceptSocket = socket.accept();
		}
		unsigned int messageCnt = 0;
		std::string  message;
		while (acceptSocket.recv(message))
		{
			std::cout << ++messageCnt << ". recv message: " << message << std::endl;
			acceptSocket.send("pong");
		}
		break;
	}

	int i = 1;
}
