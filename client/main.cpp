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
// --------------------------------------------------------------------------------

void main(int argc, const char* argv[])
{
	ParamParser paramParser(argc, argv);

	std::string  ip;
	unsigned int port;
	unsigned int count;

	if (!paramParser.get("ip",    ip   ) ||
        !paramParser.get("port",  port ) ||
		!paramParser.get("count", count))
	{
		std::cout << "use client.exe with params:" << std::endl
			      << "client.exe --ip=<address> --port=<port> --count=<count>" << std::endl;
		return;
	}

	int i = 1;
}
