#ifndef SHOW_H
#define SHOW_H

#include "../server/server.hpp"
#include <sstream>

enum show_methoes
{
    PUBLISHED = true,
    USER = false,
    PROFILE = 2,
    RECOMMEND = 3,
    DETAILS = 4
};

class Show
{
public:
  Show();
  std::string form(std::string action, std::string film_id);
  std::string table(int method, std::vector<std::vector<std::string>> films);
  std::string serach_form();
  std::string increase_money_form();
  std::string table_header();
  std::string header();
  std::string set_nav(int method);
  std::string set_table_title(int method);
  std::string set_table_body(int method, std::vector<std::string> film);
  std::string show_details(std::vector<std::string> details);
  Response* show_films(int method, std::vector<std::vector<std::string>> films, int user_id);
  Response* show_film_details(int method, std::vector<std::vector<std::string>> recom_films, std::vector<std::string> details, int user_id);
};

#endif