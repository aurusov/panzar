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
#include <vector>
// ----------------------------------------------------------------------- SYNOPSIS
#include "utils/params.h"
#include "utils/socket.h"
#include "utils/thread.h"
// --------------------------------------------------------------------------------

DWORD WINAPI item(void* pArg);

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

	typedef  std::vector<HANDLE>  HandleList;
	HandleList handleList;

	for (unsigned int i = 0; i < count; ++i)
	{
		Socket* pSocket = new Socket();
		while (!pSocket->good())
		{
			*pSocket = socket.accept();
		}
		Thread thread;
		if (!thread.create(item, pSocket))
		{
			delete pSocket;
			continue;
		}
		handleList.push_back(thread.handle());
		thread.resume();
	}

	while (::WaitForMultipleObjects(handleList.size(), &handleList[0], true, 0) == WAIT_TIMEOUT)
	{}
}

DWORD WINAPI item(void* pArg)
{
	DWORD timeStart = ::GetTickCount();

	Socket* pSocket = reinterpret_cast<Socket*>(pArg);

	unsigned int messageCnt = 0;
	std::string  message;
	while (pSocket->recv(message))
	{
		std::cout << ::GetCurrentThreadId() << ": " << ++messageCnt << ". recv message: '" << message << "'" << std::endl;
		pSocket->send("pong");
	}
	pSocket->close();
	delete pSocket;

	DWORD timeStop = ::GetTickCount();
	std::cout << ::GetCurrentThreadId() << ": work time: " << timeStop - timeStart << " msec" << std::endl;

	return 0;
}
