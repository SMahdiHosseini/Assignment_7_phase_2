#include "exceptions.h"

using namespace std;

string NotFound::what()
{
    return "Not Found";
}

string BadRequest::what()
{
    return "Bad Request";
}

string Inaccessibility::what()
{
    return "Permission Denied";
}