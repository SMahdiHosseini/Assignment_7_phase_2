#include "publisher.h"
#include "exceptions.h"

#define DEFAULT_CASH 0

using namespace std;

Publisher::Publisher(int _id, std::string _email, std::string _username, std::string _password, int _age, bool _publisher)
 : User(_id, _email, _username, _password, _age, _publisher) 
{
}

void Publisher::add_film(Film* new_film)
{
    published_films.add_film(new_film);
    send_film_register_notificatioin();
}

void Publisher::send_film_register_notificatioin()
{    
    Notification new_notif("Publisher " + username + " with id " + to_string(id) + " register new film.");
    for (int i = 0; i < follower_user.size(); i++)
        follower_user[i]->give_notification(new_notif);    
}

void Publisher::delete_film(int film_id)
{
    published_films.delete_film(film_id);
}

void Publisher::show_followers()
{
    cout << "List of Followers\n";
    cout << "#. User Id | User Username | User Email\n";
    for (int i = 0; i < follower_user.size(); i++)
    {
        cout << i + 1 << ". " << follower_user[i]->get_id() << " | ";
        cout << follower_user[i]->get_username() << " | ";
        cout << follower_user[i]->get_email() << endl;
    }
}

void Publisher::post_money(int money)
{
    cash += money;
}

void Publisher::reply_commemt(User* user, int film_id, int comment_id, string content)
{
    published_films.find_film_by_id(film_id)->reply_comment(comment_id, content);
    send_reply_notification(user);
}

void Publisher::send_reply_notification(User* user)
{
    Notification new_notif("Publisher " + username + " with id " + to_string(id) + " reply to your comment.");
    user->give_notification(new_notif);
}

void Publisher::delete_comment(int film_id, int comment_id)
{
    published_films.find_film_by_id(film_id)->delete_comment(comment_id);
}

void Publisher::add_follower(User* new_follower)
{
    follower_user.push_back(new_follower);
}

Film* Publisher::find_published_film(int film_id)
{
    return published_films.find_film_by_id(film_id);
}

void Publisher::show_films(map<string, string> optoins)
{
    published_films.show_films(optoins);
}