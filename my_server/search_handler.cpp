#include"search_handler.hpp"
#include "../Assignment7/exceptions.h"

using namespace std;


SearchHandler::SearchHandler(Network* _network) : network(_network)
{
}

Response* SearchHandler::callback(Request* req) 
{
    try
    {
        map<string, string> options;
        options["director"] = req->getBodyParam("director");
        if (network->find_logged_in_user()->check_publsher())
                return show.show_films(true, network->show_published_film(options));
        return show.show_films(false, network->search(options));
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
