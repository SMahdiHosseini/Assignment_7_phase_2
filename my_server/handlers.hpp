#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "../server/server.hpp"
#include "../Assignment7/validity.h"
#include "../Assignment7/network.h"

class Show
{
public:
  Show(Network* _network);
  Response* show_films();
  Network* network;
};

class LogoutHandler: public RequestHandler
{
public:
  LogoutHandler(Network* _network);
  Response* callback(Request*);
private:
  Network* network;
};

class LoginHandler : public RequestHandler 
{
public:
  LoginHandler(Network* _network);
  Response* callback(Request *);
protected:
  Show show;
  Validity valid;
};

class SignupHandler : public LoginHandler 
{
public:
  SignupHandler(Network* _network);
  Response* callback(Request* req);
};

class FilmHandler : public RequestHandler 
{
public:
  FilmHandler(Network* _network);
  Response* callback(Request* req);
private:
  Show show;
  Validity valid;
};


#endif