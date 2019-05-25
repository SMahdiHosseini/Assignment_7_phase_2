#ifndef USER_H
#define USER_H

#include <iostream>
#include <vector>
#include "film.h"
#include "user_repository.h"
#include "film_repository.h"
#include "notification_repository.h"

class User
{
public:
	User(int _id, std::string _email, std::string _username, std::string _password, int _age, bool _publisher);
	std::string get_username();
	std::string get_password();
	std::string get_email();
	std::vector<int> get_bought_films_id();
	int get_id();
	double get_money();
	bool check_login();
	bool check_publsher();
	void logout();
	void login_user();
	void give_notification(Notification notification); 
	void show_unread_notifications();
	void show_notifications(int limit);
	void show_bought_films(std::map<std::string, std::string> options);
	void follow_publisher(Publisher* new_pubisher);
	void increase_money(double amount);
	void buy_film(Film* neW_film, Publisher* publisher);
	void rate_film(int film_id, int score, Publisher* publisher);
	void add_comment(int film_id, std::string content, Publisher* publisher);
	void send_comment_notification(Publisher* publisher, Film* film);
	void send_follow_notification(Publisher* publisher);
	void send_buy_notification(Publisher* publisher, Film* film);
	void send_rate_notification(Publisher* publisher, Film* film);
	virtual void add_follower(User* new_follower);
	virtual void send_reply_notification(User* user);
	virtual void delete_comment(int film_id, int comment_id);
	virtual void add_film(Film* new_film);
    virtual void delete_film(int film_id);
    virtual void show_followers();
	virtual Film* find_published_film(int film_id);
    virtual void show_films(std::map<std::string, std::string> optoins);
	virtual void send_film_register_notificatioin();
    virtual void post_money(int money);
    virtual void reply_commemt(User* user, int film_id, int comment_id, std::string content);
protected:
	std::string username;
	std::string password;
	std::string email;
	int id;
	bool login;
	bool publisher;
	double cash;
	int age;
	FilmRepository bought_films;
	NotificationRepository notifications; 
	UserRepository following_publishers;
};

#endif