#ifndef __EXCEPTION_H
#define __EXCEPTION_H

#include <stdexcept>
#include <exception>
#include <new>
#include <typeinfo>

class ReadError : public std::runtime_error
{

public:
	ReadError();

};

class AddressError : public std::runtime_error
{

public:
	AddressError();

};

class ParamError : public std::runtime_error
{
public:
	ParamError();
};

class InstError : public std::runtime_error
{

public:
	InstError();

};

class UndefLabel : public std::runtime_error
{

public:
	UndefLabel();

};

class VonError : public std::runtime_error
{

public:
	VonError();

};

class JmpError : public std::runtime_error
{
	
public:
	JmpError();

};

#endif