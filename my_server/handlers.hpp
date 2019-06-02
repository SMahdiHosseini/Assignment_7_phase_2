#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "../server/server.hpp"
#include "../Assignment7/validity.h"
#include "../Assignment7/network.h"

class LoginHandler : public RequestHandler {
public:
  LoginHandler(Network* _network);
  Response *callback(Request *);
  Response* show_published_films(std::map<std::string, std::string> optoins);
  Response* show_film();
protected:
  Network* network;
  Validity valid;
};

class SignupHandler : public LoginHandler {
public:
  SignupHandler(Network* _network);
  Response* callback(Request* req);
};


#endif