/*!
  \copyright (c) Тест для panzar, 2011
  \file      socket.cpp
  \author    Урусов Андрей (drobus@gmail.com)
  \date      20.10.2011
  \brief     Описывает объект сокета и моникёр
  \indent    4T
*/

// ----------------------------------------------------------------------- INCLUDES
// ----------------------------------------------------------------------- SYNOPSIS
#include "utils/socket.h"
// --------------------------------------------------------------------------------


Socket::Socket()
	: m_socket(INVALID_SOCKET)
{}

Socket::Socket(const Socket& socket)
	: m_socket(socket.m_socket)
	, m_addr  (socket.m_addr  )
{}

Socket::Socket(const SOCKET& socket, const sockaddr_in& addr)
	: m_socket(socket)
	, m_addr  (addr  )
{}

Socket::~Socket()
{
	close();
}

Socket& Socket::operator= (const Socket& socket)
{
	close();

	m_socket = socket.m_socket;
	m_addr   = socket.m_addr;
	return *this;
}

bool Socket::create()
{
	m_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	return good();
}

void Socket::close()
{
	if (good())
	{
		closesocket(m_socket);
	}
}

bool Socket::good() const
{
	return m_socket != INVALID_SOCKET;
}

bool Socket::connect(const std::string& ip, unsigned short port)
{
	m_addr.sin_family      = AF_INET;
	m_addr.sin_addr.s_addr = inet_addr(ip.c_str());
	m_addr.sin_port        = htons(port);
	return ::connect(m_socket, (SOCKADDR*)&m_addr, sizeof(m_addr)) != SOCKET_ERROR;
}

bool Socket::bind(const std::string& ip, unsigned short port)
{
	m_addr.sin_family      = AF_INET;
	m_addr.sin_addr.s_addr = inet_addr(ip.c_str());
	m_addr.sin_port        = htons(port);
	return ::bind(m_socket, (SOCKADDR*)&m_addr, sizeof(m_addr)) != SOCKET_ERROR;
}

bool Socket::listen(unsigned int count)
{
	return ::listen(m_socket, count) != SOCKET_ERROR;
}

Socket Socket::accept() const
{
	return Socket(::accept(m_socket, NULL, NULL), m_addr);
}

// --------------------------------------------------------------------------------
// ------------- SocketInitializer
// --------------------------------------------------------------------------------
SocketInitializer::SocketInitializer()
{
	m_errorCode = WSAStartup(MAKEWORD(2, 2), &m_data);
}

SocketInitializer::~SocketInitializer()
{
	if (good())
	{
		::WSACleanup();
	}
}

bool SocketInitializer::good() const
{
	return m_errorCode == NO_ERROR;
}
