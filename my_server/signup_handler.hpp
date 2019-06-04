#ifndef SIGNUP_H
#define SIGNUP_H

#include"show.hpp"
#include"login_handler.hpp"
#include "../Assignment7/validity.h"
#include "../Assignment7/network.h"

class SignupHandler : public LoginHandler 
{
public:
  SignupHandler(Network* _network);
  Response* callback(Request* req);
};

#endif