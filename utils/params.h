/*!
  \copyright (c) Тест для panzar, 2011
  \file      params.h
  \author    Урусов Андрей (drobus@gmail.com)
  \date      19.10.2011
  \brief     Парсер параметров командной строки
  \indent    4T
*/

#ifndef _UTILS_PARAMS_H_
#define _UTILS_PARAMS_H_

// ----------------------------------------------------------------------- INCLUDES
#include <map>
#include <string>
// ----------------------------------------------------------------------- SYNOPSIS
// --------------------------------------------------------------------------------

class ParamParser
{
public:
	ParamParser(int argc, const char* argv[]);
	virtual ~ParamParser();

	template <class T>
	bool get(const std::string& name, T& value) const;

private:
	typedef std::map<std::string, std::string> ParamList;

	ParamList m_paramList;
};

#include "utils/params.inl"

#endif // _UTILS_PARAMS_H_
