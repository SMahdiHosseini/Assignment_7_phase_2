#include "details_handler.hpp"
#include "../Assignment7/exceptions.h"

using namespace std;

DetailsHandler::DetailsHandler(Network* _network) : network(_network)
{
}

Response* DetailsHandler::callback(Request* req) 
{
    try
    {
        map<string, string> options;
        int film_id = stoi(req->getBodyParam("film_id"));
        vector<string> details = network->show_film_details(film_id);
        vector<vector<string>> recom_films = network->show_recom_film(film_id);
    }
    catch(...)
    {
        throw Server::Exception("Bad request");
    }
}
