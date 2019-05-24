#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "user.h"
#include "film_repository.h"


class Publisher : public User
{
public:
    Publisher(int _id, std::string _email, std::string _username, std::string _password, int _age, bool _publisher);
    virtual void add_follower(User* new_follower);
    virtual void send_reply_notification(User* user);
    virtual void add_film(Film* new_film);
    virtual void delete_film(int film_id);
    virtual void show_followers();
    virtual Film* find_published_film(int film_id);
    virtual void send_film_register_notificatioin();
    virtual void show_films(std::map<std::string, std::string> optoins);
    virtual void post_money(int money);
    virtual void delete_comment(int film_id, int comment_id);
    virtual void reply_commemt(User* user, int film_id, int comment_id, std::string content);
private:
    std::vector<User*> follower_user;
    FilmRepository published_films;
};

#endif