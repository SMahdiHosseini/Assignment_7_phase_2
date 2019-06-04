#include "network_film_repository.h"
#include "exceptions.h"
#include "definitions.h"
#include <algorithm>

using namespace std;

NetworkFilmRepository::NetworkFilmRepository()
{
    last_id = 0;
}

Film* NetworkFilmRepository::add_new_film(int publisher_id, std::string name, int year, int length, int price, std::string summary, std::string director)
{
    last_id++;
    Film* new_film = new Film(publisher_id, last_id, name, year, length, price, summary, director);
    films.push_back(new_film);
    update_matrix_add_film(new_film->get_id());
    return new_film;
}

void NetworkFilmRepository::update_matrix_buy_film(int bought_films_id, vector<int> films_id)
{
    for (int i = 0; i < films_id.size(); ++i)
    {
        if(bought_films_id != films_id[i])
        {
            films_matrix[bought_films_id][films_id[i]]++;
            films_matrix[films_id[i]][bought_films_id]++;
        }
    }
}

void NetworkFilmRepository::update_matrix_add_film(int film_id)
{
    for(int i = 0; i < films.size(); ++i)
    {
        films_matrix[films[i]->get_id()][film_id] = 0;
        films_matrix[film_id][films[i]->get_id()] = 0;
    }
}

void NetworkFilmRepository::edit_film(int publisher_id, int film_id, std::map<std::string, std::string> edited_options)
{
    if(find_film_by_id(film_id)->get_publisher_id() == publisher_id)
    {
        find_film_by_id(film_id)->edit(edited_options);
        return;
    }
    throw Inaccessibility();
}

void NetworkFilmRepository::update_matrix_delete_film(int film_id)
{
    films_matrix[film_id][film_id] = DELETED;
}

void NetworkFilmRepository::delete_film(int film_id)
{
    for (int i = 0; i < films.size(); i++)
        if(films[i]->get_id() == film_id)
            films.erase(films.begin() + i);
    update_matrix_delete_film(film_id);
}

vector<string> NetworkFilmRepository::show_film_details(int film_id)
{
    return find_film_by_id(film_id)->show_details();
}


bool sortbysec(const pair<int,int> &first_pair,const pair<int,int> &second_pair) 
{
    if(first_pair.first < second_pair.first)
        return true;
    if(first_pair.first > second_pair.first)
        return false;
    return (first_pair.second > second_pair.second);
}

vector<pair<int, int>> NetworkFilmRepository::sort_pairs_by_weight(int film_id)
{
    vector<pair<int, int>> sort_by_weight;
    for (auto& related_films: films_matrix[film_id])
    {
        if(films_matrix[related_films.first][related_films.first] != DELETED)
            sort_by_weight.push_back(pair<int, int> (related_films.second, related_films.first));
    }
    sort(sort_by_weight.begin(), sort_by_weight.end(), sortbysec);
    return sort_by_weight;
}

bool NetworkFilmRepository::existed(vector<int> bought_films_id, int id)
{
    for (int i = 0; i < bought_films_id.size(); i++)
        if(bought_films_id[i] == id)
            return true;
    return false;
}

vector<vector<string>> NetworkFilmRepository::show_recommend_film(vector<int> bought_films_id, int film_id)
{
    vector<vector<string>> recom_films;
    cout << "Recommendation Film\n#. Film Id | Film Name | Film Length | Film Director\n";
    int counter = 1;
    vector<pair<int, int>> sorted_by_weight = sort_pairs_by_weight(film_id);
    for (int i = sorted_by_weight.size() - 1; i >= 0; i--)
    {
        if(!existed(bought_films_id, sorted_by_weight[i].second) && counter <= 4 && sorted_by_weight[i].second != film_id)
        {
            recom_films.push_back(find_film_by_id(sorted_by_weight[i].second)->show_recommend());
            counter++;
        }
    }
}
