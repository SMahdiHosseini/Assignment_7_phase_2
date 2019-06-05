#include "handlers.hpp"
#include "../Assignment7/exceptions.h"

using namespace std;

LogoutHandler::LogoutHandler(Network* _network) : network(_network)
{
}

Response* LogoutHandler::callback(Request* req)
{
    try
    {
        network->logout();
        return Response::redirect("/");
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
