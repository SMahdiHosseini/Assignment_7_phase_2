#ifndef DELETE_HANDLER_H
#define DELETE_HANDLER_H

#include "show.hpp"
#include "../Assignment7/validity.h"
#include "../Assignment7/network.h"

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