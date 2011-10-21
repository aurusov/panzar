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
#include <winsock.h>
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
	bool   send    (const std::string& message);
	bool   recv    (std::string& message);

private:
	SOCKET       m_socket;
	sockaddr_in  m_addr;
};

// --------------------------------------------------------------------------------
// ------------- noncopyable
// жесткий копипаст из буста, чтобы не ругался компилятор warning C4512
// при warning level = 4
// --------------------------------------------------------------------------------
class noncopyable
{
protected:
	noncopyable () {}
	~noncopyable() {}
private:
	noncopyable(const noncopyable&);
	const noncopyable& operator=(const noncopyable&);
};

class SocketMonicker: private noncopyable
{
public:
	SocketMonicker(Socket& socket);
	~SocketMonicker();

private:
	Socket& m_socket;
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
