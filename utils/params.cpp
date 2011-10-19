/*!
  \copyright (c) Тест для panzar, 2011
  \file      params.cpp
  \author    Урусов Андрей (drobus@gmail.com)
  \date      19.10.2011
  \brief     Парсер параметров командной строки
  \indent    4T
*/

// ----------------------------------------------------------------------- INCLUDES
#include <iostream>
// ----------------------------------------------------------------------- SYNOPSIS
#include "utils/params.h"
// --------------------------------------------------------------------------------

ParamParser::ParamParser(int argc, const char* argv[])
{
	for (int i = 1; i < argc; ++i)
	{
		std::string arg = argv[i];

		std::string::size_type pos = 0;
		while (pos < arg.size() && arg[pos] == '-')
		{
			++pos;
		}
		std::string::size_type length = arg.find('=') - pos;

		std::string name  = arg.substr(pos++, length);
		std::string value = pos < arg.size() ? arg.substr(pos + length) : "";

		std::pair<ParamList::const_iterator, bool> result = m_paramList.insert(
			ParamList::value_type(name, value)
		);

		if (!result.second)
		{
			std::cerr << "duplicate parameter " << name << "='" << value << "', ignored" << std::endl;
		}
	}
}

ParamParser::~ParamParser()
{}
