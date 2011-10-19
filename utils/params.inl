/*!
  \copyright (c) Тест для panzar, 2011
  \file      params.inl
  \author    Урусов Андрей (drobus@gmail.com)
  \date      19.10.2011
  \brief     Парсер параметров командной строки
  \indent    4T
*/

// ----------------------------------------------------------------------- INCLUDES
#include <sstream>
// ----------------------------------------------------------------------- SYNOPSIS
// --------------------------------------------------------------------------------


template <class T>
inline bool ParamParser::get(const std::string& name, T& value) const
{
	ParamList::const_iterator it = m_paramList.find(name);
	if (it == m_paramList.end())
		return false;

	std::stringstream stream;
	stream.str(it->second);
	stream >> value;

	return true;
}
