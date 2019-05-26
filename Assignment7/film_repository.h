#ifndef FILM_REPOS_H
#define FILM_REPOS_H

#include "film.h"
#include <iostream>

typedef int id;
typedef int wieght;

class FilmRepository
{
public:
    FilmRepository();
    // ~FilmRepository();
    void show_films(std::map<std::string, std::string> optiions);
    void add_film(Film* film);
    virtual void delete_film(int film_id);
    bool check_film_exists(int film_id);  
    bool in_range_film(std::map<std::string, std::string> optiions, Film* film);
    std::vector<int> in_range_films_id(std::map<std::string, std::string> optiions);
    std::vector<int> get_films_id();
    int find_user_id_with_comment_id(int film_id, int comment_id);
    Film* find_film_by_id(int film_id);
protected:
    std::vector<Film*> films;
};

#endif