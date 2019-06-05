#include "delete_handler.hpp"
#include "../Assignment7/exceptions.h"

using namespace std;

DeleteHandler::DeleteHandler(Network* _network) : network(_network)
{
}


Response* DeleteHandler::callback(Request* req) 
{
    try
    {
        map<string, string> options;
        int film_id = stoi(req->getBodyParam("film_id"));
        network->delete_film(film_id);
        return show.show_films(PUBLISHED, network->show_published_film(options));
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