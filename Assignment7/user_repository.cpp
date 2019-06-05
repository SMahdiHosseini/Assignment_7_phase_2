#include "user_repository.h"
#include "exceptions.h"
#include "user.h"
#include "publisher.h"

using namespace std;

UserRepository::UserRepository()
{
    last_id = 0;
}


bool UserRepository::check_existed_user(string username)
{
    for (int i = 0; i < users.size(); i++)
        if(users[i]->get_username() == username)
            return true;
    return false;
}

User* UserRepository::find_user(string username, string password)
{
    for (int i = 0; i < users.size(); i++)
        if(users[i]->get_username() == username && users[i]->get_password() == password)
            return users[i];
    return nullptr;
}

User* UserRepository::find_logged_in_user(int user_id)
{
    if(logged_in_users[user_id] != nullptr)
        return logged_in_users[user_id];
    throw Inaccessibility();
}

int UserRepository::signup(string email, string username, string password, int age, bool publisher)
{
    if(check_existed_user(username))
        throw BadRequest();
    last_id++;
    if(publisher)
    {
        add_publisher(email, username, password, age, publisher);
        return last_id;
    }
    User* new_user = new User(last_id,email, username, password, age, publisher);
    users.push_back(new_user);
    logged_in_users[last_id] = new_user;
    return last_id;
}

void UserRepository::add_publisher(string email, string username, string password, int age, bool publisher)
{
    Publisher* new_publisher = new Publisher(last_id, email, username, password, age, publisher);
    users.push_back(new_publisher);
    logged_in_users[last_id] = new_publisher;
}

bool UserRepository::check_publisher(int user_id)
{
    if (find_logged_in_user(user_id)->check_publsher())
        return true;
    return false;
}

int UserRepository::login(string username, string password)
{
    if(find_user(username, password) == nullptr)
        throw BadRequest();
    find_user(username, password)->login_user();
    logged_in_users[find_user(username, password)->get_id()] = find_user(username, password);
    return find_user(username, password)->get_id();
}

void UserRepository::logout(int user_id)
{
    find_user_by_id(user_id)->logout();
    logged_in_users[user_id] = nullptr;
}

Publisher* UserRepository::find_publisher_by_id(int publisher_id)
{
    for (int i = 0; i < users.size(); i++)
        if(users[i]->get_id() == publisher_id && users[i]->check_publsher())
            return (Publisher*)users[i];
    throw NotFound();
}

void UserRepository::buy_film(Film* new_film, Publisher* publisher, int user_id)
{
    find_logged_in_user(user_id)->buy_film(new_film, publisher);
}

User* UserRepository::find_user_by_id(int user_id)
{
    for (int i = 0; i < users.size(); i++)
        if(users[i]->get_id() == user_id)
            return users[i];
    throw BadRequest();
}