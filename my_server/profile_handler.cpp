#include "../Assignment7/exceptions.h"
#include "profile_handler.hpp"

using namespace std;

ProfileHandler::ProfileHandler(Network* _network) : network(_network)
{
}


Response* ProfileHandler::callback(Request* req)
{
    try
    {
        map<string, string> options;
        int user_id = stoi(req->getSessionId());
        return show.show_films(PROFILE, network->show_bought_films(options, user_id), user_id);
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