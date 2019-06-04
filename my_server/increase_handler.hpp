#ifndef INCREASE_HPP
#define INCREASE_HPP

#include "../server/server.hpp"
#include "../Assignment7/network.h"

class IncreaseHandler : public RequestHandler
{
public:
  IncreaseHandler(Network* _network);
  Response* callback(Request* req);
private:
  Network* network;
};

#endif