#ifndef PROFILE_HPP
#define PROFILR_HPP

#include "show.hpp"
#include "../Assignment7/validity.h"
#include "../Assignment7/network.h"

class ProfileHandler : public RequestHandler
{
public:
  ProfileHandler(Network* _network);
  Response* callback(Request* req);
private:
  Show show;
  Network* network;
};

#endif