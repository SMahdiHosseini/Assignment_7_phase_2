#include "home_handler.hpp"
#include "../Assignment7/exceptions.h"

using namespace std;

HomeHandler::HomeHandler(Network* _network) : network(_network)
{
}

Response* HomeHandler::callback(Request* req)
{
    try
    {
        map<string, string> options; 
        int user_id = stoi(req->getSessionId());
        if (network->find_logged_in_user(user_id)->check_publsher())
            return show.show_films(true, network->show_published_film(options, user_id), user_id);
        return show.show_films(false, network->search(options), user_id);
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