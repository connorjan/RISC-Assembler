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


#endif