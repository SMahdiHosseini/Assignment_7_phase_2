#ifndef HOME_HPP
#define HOME_HPP

#include "../Assignment7/network.h"
#include "show.hpp"

class HomeHandler : public RequestHandler
{
public:
    HomeHandler(Network* _network);
    Response* callback(Request* req);
private:
    Show show;
    Network* network;
};
#endif