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
        network->increase_money(money);
        return Response::redirect("/profile");
    }
    catch(...)
    {
        throw Server::Exception("Bad request");
    }
}