#ifndef SHOW_H
#define SHOW_H

#include "../server/server.hpp"


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
  Response* show_films(int method, std::vector<std::vector<std::string>> films);
};

#endif