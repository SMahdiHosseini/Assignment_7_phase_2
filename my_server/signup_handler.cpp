#include"signup_handler.hpp"
#include "../Assignment7/exceptions.h"
#include <iostream>
#include <string>
#include <map>
#include <sstream>

using namespace std;

SignupHandler::SignupHandler(Network* _network) : LoginHandler(_network)
{
}

Response* SignupHandler::callback(Request* req)
{
    map<string, string> elements;
    elements["username"]= req->getBodyParam("username");
    elements["password"] = req->getBodyParam("password");
    elements["email"] = req->getBodyParam("email");
    elements["age"] = req->getBodyParam("age");
    elements["publisher"] = req->getBodyParam("publisher");
    string retry_pass = req->getBodyParam("retry_password");
    if(valid.signup_validity(elements) && retry_pass == elements["password"])
    {   
        try
        {
            int user_id = network->signup(elements["email"], elements["username"], elements["password"], 
                        stoi(elements["age"]), valid.check_publisher(elements["publisher"]));
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
