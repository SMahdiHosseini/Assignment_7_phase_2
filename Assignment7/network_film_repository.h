#ifndef NET_FILM_H
#define NET_FILM_H

#include <iostream>
#include "film_repository.h"

class NetworkFilmRepository : public FilmRepository
{
public: 
    NetworkFilmRepository();
    virtual void delete_film(int film_id);
    Film* add_new_film(int publisher_id, std::string name, int year, int length, int price, std::string summary, std::string director);
    void update_matrix_add_film(int film_id);
    void update_matrix_delete_film(int film_id);
    void update_matrix_buy_film(int bought_films_id, std::vector<int> films_id);
    void edit_film(int publisher_id, int film_id, std::map<std::string, std::string> edited_options);
    void show_film_details(int film_id);
    void show_recommend_film(std::vector<int> bought_films_id, int film_id);
    bool existed(std::vector<int> bought_films_id, int id);
    std::vector<std::pair<wieght, id>> sort_pairs_by_weight(int film_id);
private:
    int last_id;
    std::map<id, std::map<id, wieght>> films_matrix;
};

#endif