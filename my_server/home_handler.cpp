#include "home_handler.hpp"

using namespace std;

HomeHandler::HomeHandler(Network* _network) : network(_network)
{
}

Response* HomeHandler::callback(Request* req)
{
    try
    {
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