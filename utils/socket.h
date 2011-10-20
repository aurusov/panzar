/*!
  \copyright (c) Тест для panzar, 2011
  \file      socket.h
  \author    Урусов Андрей (drobus@gmail.com)
  \date      20.10.2011
  \brief     Описывает объект сокета и моникёр
  \indent    4T
*/

#ifndef _UTILS_SOCKET_H_
#define _UTILS_SOCKET_H_

// ----------------------------------------------------------------------- INCLUDES
#include <winsock2.h>
#include <string>
// ----------------------------------------------------------------------- SYNOPSIS
// --------------------------------------------------------------------------------

class Socket
{
public:
	Socket();
	Socket(const Socket& socket);
	Socket(const SOCKET& socket, const sockaddr_in& addr);
	~Socket();

	Socket& operator= (const Socket& socket);

	bool   create ();
	void   close  ();
	bool   good   () const;

	bool   connect (const std::string& ip, unsigned short port);
	bool   bind    (const std::string& ip, unsigned short port);
	bool   listen  (unsigned int count);
	Socket accept  () const;

private:
	SOCKET       m_socket;
	sockaddr_in  m_addr;
};

// --------------------------------------------------------------------------------
// ------------- SocketInitializer
// --------------------------------------------------------------------------------
class SocketInitializer
{
public:
	SocketInitializer();
	~SocketInitializer();

	bool good() const;

private:
	WSADATA  m_data;
	int      m_errorCode;
};

#endif // _UTILS_SOCKET_H_
