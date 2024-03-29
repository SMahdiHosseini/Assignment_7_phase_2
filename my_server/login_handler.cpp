#include "login_handler.hpp"
#include "../Assignment7/exceptions.h"
#include <iostream>
#include <string>
#include <map>
#include <sstream>

using namespace std;


LoginHandler::LoginHandler(Network* _network) : network(_network)
{
}

Response* LoginHandler::callback(Request* req)
{
    map<string, string> elements;
    elements["username"]= req->getBodyParam("username");
    elements["password"] = req->getBodyParam("password");
    if (valid.login_validity(elements))
    {
        try
        {
            int user_id = network->login(elements["username"], elements["password"]);
            map<string, string> options; 
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
    else
        throw Server::Exception("Bad request");
}