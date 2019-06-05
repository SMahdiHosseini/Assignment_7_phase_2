#include "network.h"
#include "exceptions.h"
#include "publisher.h"

#define DEFAULT_CASH 0

using namespace std;

Network::Network()
{
    users = new UserRepository();
    films = new NetworkFilmRepository();
}

Network::~Network()
{
    delete users;
    delete films;
}

User* Network::find_logged_in_user(int user_id)
{
    if(users->find_logged_in_user(user_id) == nullptr)
        throw BadRequest();
    return users->find_logged_in_user(user_id);
}

bool Network::check_existed_user(string username)
{
    return users->check_existed_user(username);
}

int Network::signup(string email, string username, string password, int age, bool publisher)
{
    int user_id = users->signup(email, username, password, age, publisher);
    cout << "OK\n";
    return user_id;
}

int Network::login(string username, string password)
{
    int user_id = users->login(username, password);
    cout << "OK\n";
    return user_id;
}

void Network::logout(int user_id)
{
    users->logout(user_id);
    cout << "OK\n";
}

void Network::add_film(string name, int year, int length, int price, string summary, string director, int user_id)
{
    find_logged_in_user(user_id)->add_film(films->add_new_film(find_logged_in_user(user_id)->get_id(), name, year, length, price, summary, director));
    cout << "OK\n";
}

void Network::delete_film(int film_id, int user_id)
{
    if(films->find_film_by_id(film_id) == nullptr)
        throw NotFound();
    find_logged_in_user(user_id)->delete_film(film_id);
    films->delete_film(film_id);
    cout << "OK\n";
}

void Network::increase_money(int amount, int user_id)
{
    find_logged_in_user(user_id)->increase_money(amount);
    cout << "OK\n";
}

void Network::buy_film(int film_id, int user_id)
{
    Film* film = films->find_film_by_id(film_id);
    if(find_logged_in_user(user_id)->get_money() < film->get_price())
        throw BadRequest();
    users->buy_film(film, users->find_publisher_by_id(film->get_publisher_id()), user_id);
    cash[users->find_publisher_by_id(films->find_film_by_id(film_id)->get_publisher_id())->get_username()] += compute_cash(film_id);
    films->update_matrix_buy_film(films->find_film_by_id(film_id)->get_id(), find_logged_in_user(user_id)->get_bought_films_id());
    cout << "OK\n";
}

double Network::compute_cash(int film_id)
{
    double coefficient = films->find_film_by_id(film_id)->compute_coefficient();
    int price = films->find_film_by_id(film_id)->get_price();
    return price * coefficient;
}

void Network::rate_film(int film_id, int score, int user_id)
{
    find_logged_in_user(user_id)->rate_film(film_id, score, users->find_publisher_by_id(films->find_film_by_id(film_id)->get_publisher_id()));
    cout << "OK\n";
}

vector<vector<string>> Network::show_published_film(map<string, string> options, int user_id)
{
    return find_logged_in_user(user_id)->show_films(options);
}

vector<vector<string>> Network::show_bought_films(map<string, string> options, int user_id)
{
    return find_logged_in_user(user_id)->show_bought_films(options);
}

vector<vector<string>> Network::search(map<string, string> options)
{
    return films->show_films(options);
}

vector<string> Network::show_film_details(int film_id)
{
    return films->show_film_details(film_id);
}

vector<vector<string>> Network::show_recom_film(int film_id, int user_id)
{
    return films->show_recommend_film(find_logged_in_user(user_id)->get_bought_films_id(), film_id);
}