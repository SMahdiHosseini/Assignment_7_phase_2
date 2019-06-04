#ifndef DETAILS_HPP
#define DETAILS_HPP

#include "../Assignment7/network.h"
#include "show.hpp"

class DetailsHandler : public RequestHandler
{
public:
  DetailsHandler(Network* _network);
  Response* callback(Request* req);
private:
  Show show;
  Network* network;
};

#endif