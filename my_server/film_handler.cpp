#include "film_handler.hpp"
#include "../Assignment7/exceptions.h"

using namespace std;

FilmHandler::FilmHandler(Network* _network) :network(_network)
{
}

Response* FilmHandler::callback(Request* req)
{
    map<string, string> elements;
    elements["name"]= req->getBodyParam("name");
    elements["director"] = req->getBodyParam("director");
    elements["length"] = req->getBodyParam("length");
    elements["summary"] = req->getBodyParam("summary");
    elements["rate"] = req->getBodyParam("rate");
    elements["year"] = req->getBodyParam("year");
    elements["rate"] = req->getBodyParam("rate");
    elements["price"] = req->getBodyParam("price");
    int user_id = stoi(req->getSessionId());
    if(valid.add_film_validity(elements))
    {
        try
        {
            network->add_film(elements["name"], stoi(elements["year"]), stoi(elements["length"]), 
                                stoi(elements["price"]), elements["summary"], elements["director"], user_id);
            map<string, string> options;
            return show.show_films(network->find_logged_in_user(user_id)->check_publsher(), network->show_published_film(options, user_id), user_id);
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
    else
        throw Server::Exception("Bad request");
}