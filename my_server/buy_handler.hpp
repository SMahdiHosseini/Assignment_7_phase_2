#ifndef BUY_HPP
#define BUY_HPP

#include "../server/server.hpp"
#include "../Assignment7/network.h"

class BuyHandler : public RequestHandler
{
public:
    BuyHandler(Network* _network);
    Response* callback(Request* req);
private:
    Network* network;
};

#endif