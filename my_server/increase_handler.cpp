#include"increase_handler.hpp"
#include "../Assignment7/exceptions.h"

using namespace std;


IncreaseHandler::IncreaseHandler(Network* _network) : network(_network)
{
}


Response* IncreaseHandler::callback(Request* req)
{
    try
    {
        int money = stoi(req->getBodyParam("money"));
        int user_id = stoi(req->getSessionId());
        network->increase_money(money, user_id);
        return Response::redirect("/profile");
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