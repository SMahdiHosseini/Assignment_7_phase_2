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
        return show.show_films(PROFILE, network->show_bought_films(options));   
    }
    catch(...)
    {
        throw Server::Exception("Bad request");
    }
}