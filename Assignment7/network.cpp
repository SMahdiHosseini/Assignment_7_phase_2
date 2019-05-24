#include "network.h"
#include "exceptions.h"
#include "publisher.h"

#define DEFAULT_CASH 0

using namespace std;

Network::Network()
{
    users = new UserRepository(); 
    films = new FilmRepository();
}

Network::~Network()
{
    delete users;
    delete films;
}

User* Network::find_logged_in_user()
{
    if(users->find_logged_in_user() == nullptr)
        throw BadRequest();
    return users->find_logged_in_user();
}

void Network::check_login()
{
    if (users->find_logged_in_user() == nullptr)
        throw Inaccessibility();
}

bool Network::check_existed_user(string username)
{
    return users->check_existed_user(username);
}

void Network::signup(string email, string username, string password, int age, bool publisher)
{
    users->signup(email, username, password, age, publisher);
    cout << "OK\n";
}

void Network::login(string username, string password)
{
    users->login(username, password);
    cout << "OK\n";
}

void Network::logout()
{
    try
    {
        check_login();
    }
    catch(Inaccessibility e)
    {
        throw BadRequest();
    }
    users->logout();
    cout << "OK\n";
}

void Network::add_film(string name, int year, int length, int price, string summary, string director)
{
    find_logged_in_user()->add_film(films->add_new_film(find_logged_in_user()->get_id(), name, year, length, price, summary, director));
    cout << "OK\n";
}

void Network::edit_film(int film_id, map<string, string> edited_options)
{
    check_login();
    if(users->check_publisher())
    {
        films->edit_film(find_logged_in_user()->get_id(), film_id, edited_options);
        cout << "OK\n";
        return;
    }
    throw Inaccessibility();
}

void Network::delete_film(int film_id)
{
    check_login();
    if(films->find_film_by_id(film_id) == nullptr)
        throw NotFound();
    find_logged_in_user()->delete_film(film_id);
    films->delete_film(film_id);
    cout << "OK\n";
}

void Network::show_followers()
{
    find_logged_in_user()->show_followers();
}

void Network::post_money()
{
    find_logged_in_user()->post_money(cash[find_logged_in_user()->get_username()]);
    cout << "OK\n";
}

void Network::get_money()
{
    cout << find_logged_in_user()->get_money();
}

void Network::reply_comment(int film_id, int comment_id, std::string content)
{
    find_logged_in_user()->reply_commemt(users->find_user_by_id(films->find_user_id_with_comment_id(film_id, comment_id)), 
        film_id, comment_id, content);
    cout << "OK\n";
}

void Network::delete_comment(int film_id, int comment_id)
{
    find_logged_in_user()->delete_comment(film_id, comment_id);
    cout << "OK\n";
}

void Network::follow(int publisher_id)
{
    check_login();
    users->follow_publisher(publisher_id);
    cout << "OK\n";
}

void Network::increase_money(int amount)
{
    find_logged_in_user()->increase_money(amount);
    cout << "OK\n";
}

void Network::buy_film(int film_id)
{
    check_login();
    Film* film = films->find_film_by_id(film_id);
    users->buy_film(film, users->find_publisher_by_id(film->get_publisher_id()));
    cash[users->find_publisher_by_id(films->find_film_by_id(film_id)->get_publisher_id())->get_username()] += compute_cash(film_id);
    cout << "OK\n";
}

int Network::compute_cash(int film_id)
{
    return films->find_film_by_id(film_id)->comput_cahs();
}

void Network::rate_film(int film_id, int score)
{
    find_logged_in_user()->rate_film(film_id, score, users->find_publisher_by_id(films->find_film_by_id(film_id)->get_publisher_id()));
    cout << "OK\n";
}

void Network::add_comment(int film_id, string content)
{
    
    find_logged_in_user()->add_comment(film_id, content,users->find_publisher_by_id(films->find_film_by_id(film_id)->get_publisher_id()));
    cout << "OK\n";
}

void Network::show_unread_notificatioins()
{
    find_logged_in_user()->show_unread_notifications();
}

void Network::show_notifications(int limit)
{
    find_logged_in_user()->show_notifications(limit);
}

void Network::show_published_film(map<string, string> options)
{
    find_logged_in_user()->show_films(options);
}

void Network::show_bought_films(map<string, string> options)
{
    find_logged_in_user()->show_bought_films(options);
}

void Network::search(map<string, string> options)
{
    check_login();
    films->show_films(options);
}

void Network::show_film_details(int film_id)
{
    check_login();
    films->show_film_details(film_id);
    films->show_recomend_film(find_logged_in_user()->get_bought_films_id(), film_id);
}