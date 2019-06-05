#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <map>
#include "user.h"
#include "user_repository.h"
#include "film_repository.h"
#include "network_film_repository.h"

class Network
{
public:
    Network();  
    ~Network();
    int signup(std::string email, std::string username, std::string password, int age, bool publisher);
    int login(std::string username, std::string pasword);
    void add_film(std::string name, int year, int length, int price, std::string summary, std::string director, int user_id);
    void delete_film(int film_id, int user_id);
    void buy_film(int film_id, int user_id);
    void logout(int user_id);
    std::vector<std::string> show_film_details(int film_id);
    std::vector<std::vector<std::string>> show_recom_film(int film_id, int user_id);
    std::vector<std::vector<std::string>> search(std::map<std::string, std::string> options);
    void rate_film(int film_id, int score, int user_id);
    void increase_money(int amount, int user_id);
    std::vector<std::vector<std::string>> show_published_film(std::map<std::string, std::string> options, int user_id);
    std::vector<std::vector<std::string>> show_bought_films(std::map<std::string, std::string> options, int user_id);
    bool check_existed_user(std::string username);
    User* find_logged_in_user(int user_id);
    double compute_cash(int film_id);
private:
    UserRepository* users;    
    NetworkFilmRepository* films;
    std::map<std::string, double> cash;
};

#endif
