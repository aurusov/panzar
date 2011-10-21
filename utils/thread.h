/*!
  \copyright (c) Тест для panzar, 2011
  \file      thread.h
  \author    Урусов Андрей (drobus@gmail.com)
  \date      21.10.2011
  \brief     Описывает объект нити
  \indent    4T
*/

#ifndef _UTILS_THREAD_H_
#define _UTILS_THREAD_H_

// ----------------------------------------------------------------------- INCLUDES
#include <windows.h>
// ----------------------------------------------------------------------- SYNOPSIS
// --------------------------------------------------------------------------------

class Thread
{
public:
	Thread ();
	~Thread();

	typedef DWORD (WINAPI *ThreadFun)(void* pArg);

	bool create(ThreadFun pFun, void* pArg);
	bool resume();

	HANDLE handle() const;

private:
	static DWORD WINAPI main(void* pArg);

    HANDLE m_handle;
    DWORD  m_threadID;
};

#endif // _UTILS_THREAD_H_
