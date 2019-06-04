#include "film_handler.hpp"

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
    if(valid.add_film_validity(elements))
    {
        try
        {
            network->add_film(elements["name"], stoi(elements["year"]), stoi(elements["length"]), 
                                stoi(elements["price"]), elements["summary"], elements["director"]);
            map<string, string> options; 
            if (network->find_logged_in_user()->check_publsher())
                return show.show_films(true, network->show_published_film(options));
            return show.show_films(false, network->search(options));
        }
        catch(...)
        {
            throw Server::Exception("Bad request");    
        }
    }
    else
        throw Server::Exception("Bad request");
}