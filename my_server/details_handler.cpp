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
        int user_id = stoi(req->getSessionId());
        vector<string> details = network->show_film_details(film_id);
        vector<vector<string>> recom_films = network->show_recom_film(film_id, user_id);
        return show.show_film_details(network->find_logged_in_user(user_id)->check_publsher(), recom_films, details, user_id);
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
