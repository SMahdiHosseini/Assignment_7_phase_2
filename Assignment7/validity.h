#ifndef VALID_H
#define VALID_H

#include <iostream>
#include <map>

class Validity
{
public:
    Validity();
    bool check_integer(std::string integer);
    bool check_email(std::string email);
    bool check_publisher(std::string input);
    bool show_film_validity(std::map<std::string, std::string> elements);
    bool check_edit_film_validity(std::string id, std::map<std::string, std::string> elements);
    bool reply_comment_validitiy(std::map<std::string, std::string> elements);
    bool signup_validity(std::map<std::string, std::string> elements);
    bool add_film_validity(std::map<std::string, std::string> elements);
    bool login_validity(std::map<std::string, std::string> elements);
    bool check_correct_input(std::map<std::string, std::string> elements);
private:  
};

#endif