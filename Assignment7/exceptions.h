#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>

class NotFound  : public std::exception
{
public:
    virtual std::string what();
};

class BadRequest : public std::exception
{
public:
    virtual std::string what();
};

class Inaccessibility : public std::exception
{
public:
    virtual std::string what();
};

#endif