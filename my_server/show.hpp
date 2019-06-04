#ifndef SHOW_H
#define SHOW_H

#include "../server/server.hpp"
#include <sstream>

enum show_methoes
{
    PUBLISHED = true,
    USER = false,
    PROFILE = 2
};

class Show
{
public:
  Show();
  std::string table(int method, std::vector<std::vector<std::string>> films);
  std::string serach_form();
  std::string increase_money_form();
  std::string table_header();
  std::string header();
  std::string set_nav(int method);
  std::string set_table_title(int method);
  std::string set_table_body(int method, std::vector<std::string> film);
  Response* show_films(int method, std::vector<std::vector<std::string>> films);
};

#endif