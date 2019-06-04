#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "../server/server.hpp"
#include "../Assignment7/validity.h"
#include "../Assignment7/network.h"

class Show
{
public:
  Show();
  Response* show_films(int method, std::vector<std::vector<std::string>> films);
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
  Network* network;
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
  Network* network;
};

class ProfileHandler : public RequestHandler
{
public:
  ProfileHandler(Network* _network);
  Response* callback(Request* req);
private:
  Show show;
  Network* network;
};

class IncreaseHandler : public RequestHandler
{
public:
  IncreaseHandler(Network* _network);
  Response* callback(Request* req);
private:
  Network* network;
};

class SearchHandler : public RequestHandler
{
public:
  SearchHandler(Network* _network);
  Response* callback(Request* req);
private:
  Show show;
  Network* network;
};

class DeleteHandler : public RequestHandler
{
public:
  DeleteHandler(Network* _network);
  Response* callback(Request* req);
private:
  Show show;
  Network* network;
};

#endif