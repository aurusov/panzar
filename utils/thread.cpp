/*!
  \copyright (c) Тест для panzar, 2011
  \file      thread.cpp
  \author    Урусов Андрей (drobus@gmail.com)
  \date      21.10.2011
  \brief     Описывает объект нити
  \indent    4T
*/

// ----------------------------------------------------------------------- INCLUDES
#include <iostream>
// ----------------------------------------------------------------------- SYNOPSIS
#include "utils/thread.h"
#include "utils/socket.h"
// --------------------------------------------------------------------------------

Thread::Thread()
{}

Thread::~Thread()
{}

bool Thread::create(ThreadFun pFun, void* pArg)
{
	m_handle = ::CreateThread(0, 0, pFun, pArg, CREATE_SUSPENDED, &m_threadID);
	return m_handle != NULL;
}

bool Thread::resume()
{
	return ::ResumeThread(m_handle) != -1;
}

HANDLE Thread::handle() const
{
	return m_handle;
}
