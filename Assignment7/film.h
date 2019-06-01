#ifndef FILM_H
#define FILM_H

#include <map>
#include "comment.h"
#include "notification.h"
#include "comment_repository.h"

class Film
{
public:
    Film(int _publisher_id, int _id, std::string _name, int _year, int _length, int price, std::string _suumary, std::string _director);
    std::string get_name();
    std::string get_summary();
    std::string get_director();
    std::vector<std::string> show();
    int get_year();
    double compute_coefficient();
    int get_id();
    int get_length();
    int get_price();
    int get_publisher_id();
    int get_rate();
    int find_user_id_with_comment_id(int comment_id);
    std::string show_details();
    std::string show_recommend();
    void add_comment(std::string content, int user_id);
    void set_rate(int score);
    void delete_comment(int comment_id);
    void reply_comment(int comment_id, std::string content);
    void edit(std::map<std::string, std::string> edited_options);
    void edit_fields(std::string key, std::string value);
private:
    std::string name;
    std::string summary;
    std::string director;
    int year;
    int id;
    int publisher_id;
    double score;
    int length;
    int price;
    int rate_count;
    CommentRepository comments;
};

#endif
