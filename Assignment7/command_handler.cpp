#include "command_handler.h"
#include "exceptions.h"
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>   
#include <map>

using namespace std;

CommandHandler::CommandHandler() : valid()
{
    network = new Network();
}

CommandHandler::~CommandHandler()
{
    delete network;
}

void CommandHandler::run()
{
    string input_string;
    while (getline(cin, input_string))
    {
        try
        {
            input = split_string(input_string);
            if(input.size() == 0)
                continue;
            detect_instruction_methode();   
        }
        catch(BadRequest& e)
        {
            cout << e.what() << '\n';
        }
        catch(Inaccessibility& e)
        {
            cout << e.what() << '\n';
        }
        catch(NotFound& e)
        {
            cout << e.what() << '\n';
        }
    }
}

string_list CommandHandler::split_string(string input)
{
    stringstream input_string_stream(input);
    return vector<string>(istream_iterator<string>(input_string_stream),
            istream_iterator<string>());
}

void CommandHandler::detect_instruction_methode()
{
    if(input[INSTRUCTION_TYPE_INDEX] == POST)
    {
        post_methode_instructions();
        return;
    }
    if(input[INSTRUCTION_TYPE_INDEX] == GET)
    {
        get_methode_instructions();
        return;
    }
    if(input[INSTRUCTION_TYPE_INDEX] == PUT)
    {
        put_methode_instructions();
        return;
    }
    if(input[INSTRUCTION_TYPE_INDEX] == DELETE)
    {
        delete_methode_instructions();
        return;
    }
    throw BadRequest();
}

void CommandHandler::get_methode_instructions()
{
    if(input[INSTRUCTION_ACTION_INDEX] == FOLLOWERS)
    {
        network->show_followers();
        return;
    }
    if(input[INSTRUCTION_ACTION_INDEX] == PUBLISHED)
    {
        show_films(PUBLISHED);
        return;
    }
    if(input[INSTRUCTION_ACTION_INDEX] == FILMS)
    {
        show_films(FILMS);
        return;
    }
    if(input[INSTRUCTION_ACTION_INDEX] == PURCHASED)
    {
        show_films(PURCHASED);
        return;
    }
    if(input[INSTRUCTION_ACTION_INDEX] == NOTIFICATIONS)
    {
        show_notifications();
        return;
    }
    throw BadRequest();
}

void CommandHandler::delete_methode_instructions()
{
    if(input[INSTRUCTION_ACTION_INDEX] == FILMS)
    {
        delete_film();
        return;
    }
    if(input[INSTRUCTION_ACTION_INDEX] == COMMENTS)
    {
        delete_comment();
        return;
    }
    throw BadRequest();
}

void CommandHandler::put_methode_instructions()
{
    if(input[INSTRUCTION_ACTION_INDEX] == FILMS)
    {
        edit_film();
        return;
    }
    throw BadRequest();
}

void CommandHandler::post_methode_instructions()
{
    if(input[INSTRUCTION_ACTION_INDEX] == SIGNUP)
    {
        signup();
        return;
    }
    if(input[INSTRUCTION_ACTION_INDEX] == LOGIN)
    {
        login();
        return;
    }
    if(input[INSTRUCTION_ACTION_INDEX] == FILMS)
    {
        add_film();
        return;
    }
    if(input[INSTRUCTION_ACTION_INDEX] == MONEY && find_index(SEPERATOR) == INSTRUCTION_ACTION_INDEX)
    {    
        post_money();
        return;
    }
    if(input[INSTRUCTION_ACTION_INDEX] == REPLIES)
    {   
        reply_comment();
        return;
    }
    if(input[INSTRUCTION_ACTION_INDEX] == FOLLOWERS)
    {   
        follow();
        return;
    }
    if(input[INSTRUCTION_ACTION_INDEX] == MONEY && input[INSTRUCTION_SEPERATOR_INDEX] == SEPERATOR)
    {   
        increase_money();
        return;
    }
    if(input[INSTRUCTION_ACTION_INDEX] == BUY)
    {   
        buy_film();
        return;
    }
    if(input[INSTRUCTION_ACTION_INDEX] == RATE)
    {
        rate_film();
        return;
    }
    if(input[INSTRUCTION_ACTION_INDEX] == COMMENTS)
    {    
        add_comment();
        return;
    }
    throw BadRequest();
}

void CommandHandler::show_notifications()
{
    if(find_index(SEPERATOR) != INSTRUCTION_SEPERATOR_INDEX)
    {
        network->show_unread_notificatioins();
        return;
    }
    string limit = input[find_index("limit") + 1];
    if(valid.check_integer(limit))
        network->show_notifications(stoi(limit));
    else
        throw BadRequest();
}

bool CommandHandler::show_details()
{
    if(find_index(FILM_ID) != INSTRUCTION_ACTION_INDEX)
    {
        string film_id = input[find_index(FILM_ID) + 1];
        if (valid.check_integer(film_id))
        {
            network->show_film_details(stoi(film_id));
            return true;
        }
        else
            throw BadRequest();
    }
    return false;
}

bool CommandHandler::show_all(map<string, string> elements,string type)
{
    if(find_index(SEPERATOR) != INSTRUCTION_SEPERATOR_INDEX)
    {
        elements[EMPTY] = EMPTY;
        if(type == PUBLISHED)
            network->show_published_film(elements);
        if(type == FILMS)
            network->search(elements);
        if(type == PURCHASED)
            network->show_bought_films(elements);
        return true;
    }
    return false;
}

void CommandHandler::show_films(string type)
{
    map<string, string> elements;
    if(show_all(elements, type))
        return;
    if(show_details())
        return;
    if(find_index(NAME) != INSTRUCTION_ACTION_INDEX)
        elements[NAME] = input[find_index(NAME) + 1];
    if(find_index("min_year") != INSTRUCTION_ACTION_INDEX)
        elements["min_year"] = input[find_index("min_year") + 1];
    if(find_index("min_rate") != INSTRUCTION_ACTION_INDEX)
        elements["min_rate"] = input[find_index("min_rate") + 1];
    if(find_index(PRICE) != INSTRUCTION_ACTION_INDEX)
        elements[PRICE] = input[find_index(PRICE) + 1];
    if(find_index(DIRECTOR) != INSTRUCTION_ACTION_INDEX)
        elements[DIRECTOR] = input[find_index(DIRECTOR) + 1];
    if(find_index("max_year") != INSTRUCTION_ACTION_INDEX)
        elements["max_year"] = input[find_index("max_year") + 1];
    if(valid.show_film_validity(elements))
    {
        if(type == PURCHASED)
            network->show_bought_films(elements);
        if(type == PUBLISHED)
            network->show_published_film(elements);
        if(type == FILMS)
            network->search(elements);
    }
    else
        throw BadRequest();
}

void CommandHandler::delete_film()
{
    string film_id = input[find_index(FILM_ID) + 1];
    if(valid.check_integer(film_id))
        network->delete_film(stoi(film_id));
    else
        throw BadRequest();
}

void CommandHandler::delete_comment()
{
    string film_id = input[find_index(FILM_ID) + 1];
    string comment_id = input[find_index(COMMENT_ID) + 1];
    if(valid.check_integer(film_id) && valid.check_integer(comment_id))
        network->delete_comment(stoi(film_id), stoi(comment_id));
    else
        throw BadRequest();
}
void CommandHandler::edit_film()
{
    map<string, string> elements; 
    string film_id = input[find_index(FILM_ID) + 1];
    if(find_index(NAME) != INSTRUCTION_ACTION_INDEX)
        elements[NAME] = input[find_index(NAME) + 1];
    if(find_index(YEAR) != INSTRUCTION_ACTION_INDEX)
        elements[YEAR] = input[find_index(YEAR) + 1];
    if(find_index(LENGTH) != INSTRUCTION_ACTION_INDEX)
        elements[LENGTH] = input[find_index(LENGTH) + 1];
    if(find_index(SUMMARY) != INSTRUCTION_ACTION_INDEX)
        elements[SUMMARY] = input[find_index(SUMMARY) + 1];
    if(find_index(DIRECTOR) != INSTRUCTION_ACTION_INDEX)
        elements[DIRECTOR] = input[find_index(DIRECTOR) + 1];
    if(valid.check_edit_film_validity(film_id, elements))
        network->edit_film(stoi(film_id), elements);
    else
        throw BadRequest();
}

void CommandHandler::add_comment()
{
    string film_id = input[find_index(FILM_ID) + 1];
    string content = input[find_index(CONTENT) + 1];
    if(valid.check_integer(film_id))
        network->add_comment(stoi(film_id), content);
    else
        throw BadRequest();
}

void CommandHandler::rate_film()
{
    string film_id = input[find_index(FILM_ID) + 1];
    string score = input[find_index(SCORE) + 1];
    if(valid.check_integer(film_id) && valid.check_integer(score))
        network->rate_film(stoi(film_id), stoi(score));
    else
        throw BadRequest();
}

void CommandHandler::follow()
{
    string user_id = input[find_index(USER_ID) + 1];
    if(valid.check_integer(user_id))
        network->follow(stoi(user_id));
    else 
        throw BadRequest();
}

void CommandHandler::buy_film()
{
    string film_id = input[find_index(FILM_ID) + 1];
    if(valid.check_integer(film_id))
        network->buy_film(stoi(film_id));
    else
        throw BadRequest();
}

void CommandHandler::reply_comment()
{
    map<string, string> elements;
    elements[FILM_ID] = input[find_index(FILM_ID) + 1];
    elements[COMMENT_ID] = input[find_index(COMMENT_ID) + 1];
    elements[CONTENT] = input[find_index(CONTENT) + 1];
    if(valid.reply_comment_validitiy(elements))
        network->reply_comment(stoi(elements[FILM_ID]), stoi(elements[COMMENT_ID]), elements[CONTENT]);
    else
        throw BadRequest();
}

void CommandHandler::increase_money()
{
    string amount = input[find_index(AMOUNT) + 1];
    if(valid.check_integer(amount))
        network->increase_money(stoi(amount));
    else
        throw BadRequest();
}

void CommandHandler::signup()
{
    map<string, string> elements;
    elements[USERNAME] = input[find_index(USERNAME) + 1];
    elements[PASS] = input[find_index(PASS) + 1];
    elements[AGE] = input[find_index(AGE) + 1];
    elements[PUBLISHER] = input[find_index(PUBLISHER) + 1];
    elements[EMAIL] = input[find_index(EMAIL) + 1];
    if(valid.signup_validity(elements))
    {
        network->signup(elements[EMAIL], elements[USERNAME], elements[PASS], 
                        stoi(elements[AGE]), check_publisher(elements[PUBLISHER]));
    }
    else
        throw BadRequest();
}

void CommandHandler::login()
{
    map<string, string> elements;
    elements[USERNAME] = input[find_index(USERNAME) + 1];
    elements[PASS] = input[find_index(PASS) + 1];
    if(valid.login_validity(elements))
        network->login(elements[USERNAME], elements[PASS]);
    else
        throw BadRequest();
}

void CommandHandler::post_money()
{
    network->get_money();
}

void CommandHandler::add_film()
{
    map<string, string> elements;
    elements[NAME] = input[find_index(NAME) + 1];
    elements[YEAR] = input[find_index(YEAR) + 1];
    elements[LENGTH] = input[find_index(LENGTH) + 1];
    elements[PRICE] = input[find_index(PRICE) + 1];
    elements[SUMMARY] = input[find_index(SUMMARY) + 1];
    elements[DIRECTOR] = input[find_index(DIRECTOR) + 1];
    if(valid.add_film_validity(elements))
        network->add_film(elements[NAME], stoi(elements[YEAR]),
                            stoi(elements[LENGTH]), stoi(elements[PRICE]),
                            elements[SUMMARY], elements[DIRECTOR]);
    else
        throw BadRequest();
}

int CommandHandler::find_index(string key)
{
    for (int i = 0; i < input.size(); i++)
        if(input[i] == key)
            return i;
    return INSTRUCTION_ACTION_INDEX;
}

bool CommandHandler::check_publisher(string publisher)
{
    if(publisher == "true")
        return true;
    if(publisher == "false" || publisher == "?")
        return false;
}   