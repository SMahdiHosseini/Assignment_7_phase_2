#ifndef FILMHAND_H
#define FILMHAND_H

#include "show.hpp"
#include "../Assignment7/validity.h"
#include "../Assignment7/network.h"

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

#endif