#ifndef USER_REPOS_H
#define USER_REPOS_H

#include <iostream>
#include <vector>
#include "film.h"

class User;

class Publisher;

class UserRepository
{
public:
    UserRepository();
    // ~UserRepository();
    int signup(std::string email, std::string username, std::string password, int age, bool publisher);
    void add_publisher(std::string email, std::string username, std::string password, int age, bool publisher);
    int login(std::string username, std::string pasword);
    void logout(int user_id);
    void buy_film(Film* new_film, Publisher* publisher, int user_id);
    bool check_existed_user(std::string username);
    bool check_publisher(int user_id);
    Publisher* find_publisher_by_id(int user_id);
    User* find_user(std::string username, std::string password);
    User* find_logged_in_user(int user_id);
    User* find_user_by_id(int user_id);
private:
    int last_id;
    std::vector<User*> users;    
    std::map<int , User*> logged_in_users;
};

#endif