#include "definitions.h"
#include "validity.h"
#include <regex>

using namespace std;

Validity::Validity()
{}

bool Validity::check_correct_input(map<string, string> elements)
{
    for(auto& element: elements)
        if(element.second == SEPERATOR && element.first != PUBLISHER)
            return false;
    return true;
}

bool Validity::signup_validity(map<string, string> elements)
{
    return check_correct_input(elements) && check_integer(elements[AGE]) && check_email(elements[EMAIL]) && check_publisher(elements[PUBLISHER]);
}

bool Validity::add_film_validity(map<string, string> elements)
{
    return check_correct_input(elements) && check_integer(elements[YEAR]) && check_integer(elements[LENGTH]) && check_integer(elements[PRICE]);
}

bool Validity::login_validity(map<string, string> elements)
{
    return check_correct_input(elements);
}

bool Validity::check_integer(string integer)
{
    for (int i = 0; i < integer.size(); i++)
        if(integer[i] > '9' || integer[i] < '0')
            return false;
    return true;
}

bool Validity::check_email(string email)
{
    const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
   return regex_match(email, pattern);
}

bool Validity::check_publisher(string publisher)
{
    if(publisher == "true" || publisher == "false" || publisher == "?")
        return true;
    return false;
}

bool Validity::reply_comment_validitiy(map<string, string> elements)
{
    return check_correct_input(elements) && check_integer(elements[FILM_ID]) && check_integer(elements[COMMENT_ID]);
}

bool Validity::check_edit_film_validity(string id, map<string, string> elements)
{
    bool flag = true; 
    for(auto& element: elements)
        if(element.first == YEAR || element.first == LENGTH)
            flag = check_integer(element.second);
    return check_integer(id) && flag && check_correct_input(elements);
}

bool Validity::show_film_validity(map<string, string> elements)
{
    bool flag = true;
    for(auto& element: elements)
        if(element.first == "min_year" || element.first == "max_year" || element.first == PRICE || element.first == "min_rate")
            flag = check_integer(element.second);
    return flag && check_correct_input(elements);
}