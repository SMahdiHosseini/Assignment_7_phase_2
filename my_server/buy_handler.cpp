#include "buy_handler.hpp"
#include "../Assignment7/exceptions.h"

using namespace std;

BuyHandler::BuyHandler(Network* _network) : network(_network)
{
}

Response* BuyHandler::callback(Request* req)
{
    try
    {
        int film_id = stoi(req->getBodyParam("film_id"));
        network->buy_film(film_id);
        return Response::redirect("/profile");
    }
    catch(BadRequest e)
    {
        throw Server::Exception("Bad request");
    }
    catch(Inaccessibility e)
    {
        throw Server::Exception("permission denied");
    }
    catch(NotFound e)
    {
        throw Server::Exception("Not Found");
    }
}