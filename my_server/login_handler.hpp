#ifndef LOGIN_H
#define LOGIN_H

#include "show.hpp"
#include "../Assignment7/validity.h"
#include "../Assignment7/network.h"


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

#endif