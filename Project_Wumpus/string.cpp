#include "string.h"
#include <iostream>
#include <cstring>
#include <climits>
#include <cassert>

sfw::string::string(void)
{
	m_data = new char[m_size = 1]{ '\0' };
}

sfw::string::~string()
{
	delete[]m_data;
	m_data = nullptr;
}

size_t sfw::string::length() const
{
	if(m_data != nullptr) return strlen(m_data);
	else return 0;
}





sfw::string::string(size_t size)
{
	m_size = size;
	m_data = new char[m_size]{ '\0' };
}

sfw::string::string(const char * a, size_t size)
{
	m_size = size;
	if (m_size > 0)
	{
		m_data = new char[m_size];
		memcpy(m_data, a, m_size);
		m_data[m_size - 1] = '\0';
	}
	else 
	{
		m_size = 1;
		m_data = new char[m_size];
		m_data[0] = '\0';
	}
}

sfw::string::string(const char * a)
{
	if (a != nullptr && a != "")
	{
		m_size = strlen(a) + 1;
		m_data = new char[m_size] { '\0' };
		memcpy(m_data, a, m_size);
		m_data[m_size - 1] = '\0';
	}
	else
	{
		m_data = new char[m_size = 1]{ '\0' };
	}
}

sfw::string::string(const string & a)
{
	m_size = a.m_size;
	m_data = new char[m_size];
	memcpy(m_data, a.m_data, m_size);
}

sfw::string::string(string && a) : m_data(a.m_data), m_size(a.m_size)
{
	//Credit - Had to look up on CPP Reference to be certain.
	a.m_data = nullptr;
	a.m_size = 0;
}

sfw::string & sfw::string::operator=(const string & a)
{
	delete[] m_data;
	m_size = a.m_size;
	m_data = new char[m_size];
	memcpy(m_data, a.m_data, m_size);
	return *this;
}

sfw::string & sfw::string::operator=(string && a)
{
	//Credit - Had to look up on CPP Reference for help.
	delete[] m_data;
	m_data = a.m_data;
	a.m_data = nullptr;
	a.m_size = 0;
	return *this;
}

sfw::string & sfw::string::operator=(const char * a)
{
	delete[] m_data;
	m_size = strlen(a) + 1;
	m_data = new char[m_size];
	memcpy(m_data, a, m_size);
	m_data[m_size - 1] = '\0';
	return *this;
}

sfw::string & sfw::string::operator+=(const string & a)
{
	resize(m_size + a.m_size);
	strcat_s(m_data, m_size, a.m_data);
	return *this;
}

sfw::string & sfw::string::operator+=(const char * a)
{
	resize(m_size + strlen(a) + 1);
	strcat_s(m_data, m_size, a);
	return *this;
}

sfw::string & sfw::string::operator+=(char a)
{
	resize(m_size + 2);
	m_data[m_size - 2] = a;
	m_data[m_size - 1] = '\0';
	return *this;
}

char & sfw::string::operator[](size_t index)
{
	return this->m_data[index];
}

const char & sfw::string::operator[](size_t index) const
{
	return this->m_data[index];
}




size_t sfw::string::size() const
{
	return m_size;
}

void sfw::string::resize(size_t size)
{
	//Credit - Had to ask Esme for appropriate max size
	string temp = string(*this);
	delete[] m_data;
	m_size = size;
	if (m_size < 1) m_size = 1;
	if (m_size > UINT16_MAX) m_size = UINT16_MAX;
	m_data = new char[m_size];
	memcpy(m_data, temp.m_data, m_size);
	m_data[temp.m_size - 1] = '\0';
}

void sfw::string::clear()
{
	m_data[0] = '\0';
}

bool sfw::string::empty() const
{
	if (m_data[0] == '\0') return true;
	else return false;
}

const char * sfw::string::cstring() const
{
	return m_data;
}

bool sfw::operator<(const string & a, const string & b)
{
	if (strcmp(a.cstring(), b.cstring()) < 0) return true;
	return false;
}

bool sfw::operator<(const string & a, const char * b)
{
	if (strcmp(a.cstring(), b) < 0) return true;
	return false;
}

bool sfw::operator<(const char * a, const string & b)
{
	if (strcmp(a, b.cstring()) < 0) return true;
	return false;
}

bool sfw::operator<=(const string & a, const string & b)
{
	if (strcmp(a.cstring(), b.cstring()) <= 0) return true;
	return false;
}

bool sfw::operator<=(const string & a, const char * b)
{
	if (strcmp(a.cstring(), b) <= 0) return true;
	return false;
}

bool sfw::operator<=(const char * a, const string & b)
{
	if (strcmp(a, b.cstring()) <= 0) return true;
	return false;
}

bool sfw::operator>(const string & a, const string & b)
{
	if (strcmp(a.cstring(), b.cstring()) > 0) return true;
	return false;
}

bool sfw::operator>(const string & a, const char * b)
{
	if (strcmp(a.cstring(), b) > 0) return true;
	return false;
}

bool sfw::operator>(const char * a, const string & b)
{
	if (strcmp(a, b.cstring()) > 0) return true;
	return false;
}

bool sfw::operator>=(const string & a, const string & b)
{
	if (strcmp(a.cstring(), b.cstring()) >= 0) return true;
	return false;
}

bool sfw::operator>=(const string & a, const char * b)
{
	if (strcmp(a.cstring(), b) >= 0) return true;
	return false;
}

bool sfw::operator>=(const char * a, const string & b)
{
	if (strcmp(a, b.cstring()) >= 0) return true;
	return false;
}

bool sfw::operator!=(const string & a, const string & b)
{
	if (strcmp(a.cstring(), b.cstring()) != 0) return true;
	return false;
}

bool sfw::operator!=(const string & a, const char * b)
{
	if (strcmp(a.cstring(), b) != 0) return true;
	return false;
}

bool sfw::operator!=(const char * a, const string & b)
{
	if (strcmp(a, b.cstring()) != 0) return true;
	return false;
}

bool sfw::operator==(const string & a, const string & b)
{
	if (strcmp(a.cstring(), b.cstring()) == 0) return true;
	return false;
}

bool sfw::operator==(const string & a, const char * b)
{
	if (strcmp(a.cstring(), b) == 0) return true;
	return false;
}

bool sfw::operator==(const char * a, const string & b)
{
	if (strcmp(a, b.cstring()) == 0) return true;
	return false;
}

sfw::string sfw::operator+(const string & a, const string & b)
{
	string tempString = string(a);
	tempString += b;
	return tempString;
}

sfw::string sfw::operator+(const string & a, const char * b)
{
	string tempString = string(a);
	tempString += b;
	return tempString;
}

sfw::string sfw::operator+(const char * a, const string & b)
{
	string tempString = string(a);
	tempString += b;
	return tempString;
}

sfw::string sfw::operator+(const string & a, char b)
{
	string tempString = string(a);
	tempString += b;
	return tempString;
}

sfw::string sfw::operator+(char a, const string & b)
{
	string tempString = string(a);
	tempString += b;
	return tempString;
}

std::ostream & sfw::operator<<(std::ostream & os, const string & p)
{
	os << p.cstring();
	return os;
}

std::istream & sfw::operator>>(std::istream & is, string & p)
{
	//Credit - Had to ask Esme for help fixing a memory leak
	char temp[80];
	is >> temp;
	p = string(temp);
	return is;
}

const sfw::string sfw::literals::operator""_sfw(const char * a, size_t len)
{
	return string(a,len + 1);
}
