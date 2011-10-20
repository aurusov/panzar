/*!
  \copyright (c) Тест для panzar, 2011
  \file      main.cpp
  \author    Урусов Андрей (drobus@gmail.com)
  \date      19.10.2011
  \brief     Клиентский модуль
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
		          << "client.exe --ip=<server_address> --port=<server_port> --count=<messages_count>" << std::endl;
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

	if (!socket.connect(ip, port))
	{
		std::cerr << "socket connection error: " << WSAGetLastError() << std::endl;
		return;
	}

	static const std::string s_message("Hello world!");
	for (unsigned int i = 0; i < count; ++i)
	{
		if (socket.send(s_message))
		{
			std::cout << i + 1 << ". send message '" << s_message << "' ok" << std::endl;
			std::string pong;
			if (!socket.recv(pong))
			{
				std::cerr << "socket recv error: " << WSAGetLastError() << std::endl;
			}
		}
		else
		{
			std::cerr << "socket send error: " << WSAGetLastError() << std::endl;
		}
	}
}
