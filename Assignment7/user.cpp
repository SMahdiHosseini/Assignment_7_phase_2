#include "user.h"
#include "exceptions.h"
#include "publisher.h"
#define DEFAULT_CASH 0

using namespace std;

User::User(int _id, std::string _email, std::string _username, std::string _password, int _age, bool _publisher)
{
    email = _email;
    username = _username;
    password = _password;
    age = _age;
    id = _id;
    publisher = _publisher;
    login = true;
    cash = DEFAULT_CASH;
}

void User::follow_publisher(Publisher* new_publisher)
{
    following_publishers.add_existed_publisher(new_publisher);
    new_publisher->add_follower(this);
    send_follow_notification(new_publisher);
}

void User::send_follow_notification(Publisher* publisher)
{
    Notification new_notif("User " + username + " with id " + to_string(id) + " follow you.");
    publisher->give_notification(new_notif);
}

void User::give_notification(Notification notification)
{
    notifications.give_notification(notification);
}

void User::buy_film(Film* new_film, Publisher* publisher)
{
    bought_films.add_film(new_film);
    send_buy_notification(publisher, new_film);
}

void User::send_buy_notification(Publisher* publisher, Film* film)
{
    Notification new_notif("User " + username + " with id " + to_string(id) + 
        " buy your film " + film->get_name() + " with id " + to_string(film->get_id()) + ".");
    publisher->give_notification(new_notif);
}

void User::rate_film(int film_id, int score, Publisher* publisher)
{
    try
    {
        Film* film = bought_films.find_film_by_id(film_id);
        film->set_rate(score);
        send_rate_notification(publisher , film);
    }
    catch(NotFound e)
    {
        throw Inaccessibility();
    }
}

void User::send_rate_notification(Publisher* publisher, Film* film)
{
    Notification new_notif("User " + username + " with id " + to_string(id) + 
        " rate your film " + film->get_name() + " with id " + to_string(film->get_id()) + ".");
    publisher->give_notification(new_notif);
}

void User::add_comment(int film_id, string content, Publisher* publisher)
{
    try
    {
        bought_films.find_film_by_id(film_id)->add_comment(content, id);
        send_comment_notification(publisher, bought_films.find_film_by_id(film_id));
    }
    catch(NotFound e)
    {
        throw Inaccessibility();
    }
}

void User::send_comment_notification(Publisher* publisher, Film* film)
{
    Notification new_notif("User " + username + " with id " + to_string(id) + 
        " comment on your film " + film->get_name() + " with id " + to_string(film->get_id()) + ".");
    publisher->give_notification(new_notif);
}

void User::show_unread_notifications()
{
    notifications.show_unread_notifications();
}

void User::show_notifications(int limit)
{
    notifications.show_notifications(limit);
}

void User::increase_money(int amount)
{
    cash += amount;
}

void User::show_bought_films(map<string, string> options)
{
    bought_films.show_films(options);
}

vector<int> User::get_bought_films_id()
{
    return bought_films.get_films_id();
}

string User::get_username()
{
    return username;
}

string User::get_password()
{
    return password;
}

string User::get_email()
{
    return email;
}

int User::get_id()
{
    return id;
}

int User::get_money()
{
    return cash;
}

bool User::check_login()
{
    return login;
}

bool User::check_publsher()
{
    return publisher;
}

void User::logout()
{
    login = false;
}

void User::login_user()
{
    login = true;
}

void User::add_film(Film* new_film)
{
    throw Inaccessibility() ;
}

void User::delete_film(int film_id)
{
    throw Inaccessibility();
}

void User::show_followers()
{
    throw Inaccessibility();
}

void User::post_money(int money)
{
    throw Inaccessibility();
}

void User::reply_commemt(User* user, int film_id, int comment_id, string comtent)
{
    throw Inaccessibility();
}

void User::delete_comment(int film_id, int comment_id)
{
    throw Inaccessibility();
}

void User::add_follower(User* new_follower)
{
    throw Inaccessibility();
}

void User::send_reply_notification(User* user)
{
    throw Inaccessibility();
}

Film* User::find_published_film(int film_id)
{
    throw Inaccessibility();
}

void User::send_film_register_notificatioin()
{
    throw Inaccessibility();
}

void User::show_films(std::map<string, string> optoins)
{
    throw Inaccessibility();
}