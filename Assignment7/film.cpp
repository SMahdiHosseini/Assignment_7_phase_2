#include "film.h"

#define NAME "name"
#define YEAR "year"
#define LENGTH "length"
#define SUMMATY "summary"
#define DIRECTOR "director"

using namespace std;

Film::Film(int _publisher_id, int _id, string _name, int _year, int _length, int _price, string _suumary, string _director)
    : comments()
{
    name = _name;
    summary = _suumary;
    director = _director;
    year = _year;
    id = _id;
    publisher_id = _publisher_id;
    length = _length;
    price = _price;
    score = 0;
    rate_count = 0;
}

int Film::get_id()
{
    return id;
}

int Film::get_publisher_id()
{
    return publisher_id;
}

string Film::get_name()
{
    return name;
}

string Film::get_director()
{
    return director;
}

int Film::get_length()
{
    return length;
}

int Film::get_price()
{
    return price;
}

int Film::get_rate()
{
    return score;
}

int Film::get_year()
{
    return year;
}

void Film::edit_fields(string key, string value)
{
    if(key == NAME)
        name = value;
    if(key == YEAR)
        year = stoi(value);
    if(key == LENGTH)
        length = stoi(value);
    if(key == SUMMATY)
        summary = value;
    if(key == DIRECTOR)
        director = value;
}

void Film::edit(map<string, string> edited_options)
{
    for(auto& option : edited_options)
        edit_fields(option.first, option.second);
}

void Film::reply_comment(int comment_id, string content)
{
    comments.find_comment_by_id(comment_id)->reply_content(content);
}

void Film::delete_comment(int comment_id)
{
    comments.delete_comment(comment_id);
}

void Film::set_rate(int new_score)
{
    score = (score * rate_count + new_score) / (rate_count + 1);
    rate_count++;
}

int Film::find_user_id_with_comment_id(int comment_id)
{
    return comments.find_user_id_with_comment_id(comment_id);
}

void Film::add_comment(string content, int user_id)
{
    comments.add_comment(content, user_id);
}

double Film::compute_coefficient()
{
    if(score < 5)
        return 0.8;
    if(score >= 5 && score < 8)
        return 0.9;
    if(score >= 8)
        return 0.95;
}

vector<string> Film::show()
{
    vector<string> show;
    show.push_back(to_string(id));
    show.push_back(name);
    show.push_back(to_string(price));
    show.push_back(to_string(year));
    show.push_back(to_string(length)); 
    show.push_back(to_string((int) ((score * 100.0) / 100.0)));
    show.push_back(director);
    return show;
}

vector<string> Film::show_details()
{
    vector<string> details;
    details.push_back(name);
    details.push_back(to_string(id));
    details.push_back(director);
    details.push_back(to_string(length));
    details.push_back(to_string(year));
    details.push_back(summary);
    details.push_back(to_string((int) ((score * 100.0) / 100.0)));
    details.push_back(to_string(price));
    details.push_back(comments.show_comments());
    return details;
}

vector<string> Film::show_recommend()
{
    vector<string> show_recom;
    show_recom.push_back(to_string(id));
    show_recom.push_back(name);
    show_recom.push_back(to_string(length));
    show_recom.push_back(director);
    return show_recom;
}