#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <map>
#include "user.h"
#include "user_repository.h"
#include "film_repository.h"

class Network
{
public:
    Network();  
    ~Network();
    void check_login();
    void signup(std::string email, std::string username, std::string password, int age, bool publisher);
    void login(std::string username, std::string pasword);
    void add_film(std::string name, int year, int length, int price, std::string summary, std::string director);
    void edit_film(int film_id, std::map<std::string, std::string> edited_options);
    void delete_film(int film_id);
    void follow(int publisher_id);
    void buy_film(int film_id);
    void show_followers();
    void logout();
    void show_film_details(int film_id);
    void post_money();
    void get_money();
    void search(std::map<std::string, std::string> options);
    void add_comment(int film_id, std::string content);
    void rate_film(int film_id, int score);
    void increase_money(int amount);
    void reply_comment(int film_id, int comment_id, std::string content);
    void delete_comment(int film_id, int comment_id);
    void show_unread_notificatioins();
    void show_notifications(int limit);
    void show_published_film(std::map<std::string, std::string> options);
    void show_bought_films(std::map<std::string, std::string> options);
    double compute_cash(int film_id);
    int network_money();
    bool check_existed_user(std::string username);
    User* find_logged_in_user();
private:
    User* admin;
    UserRepository* users;    
    FilmRepository* films;
    std::map<std::string, double> cash;
};

#endif