#include "film_repository.h"
#include "exceptions.h"
#include "definitions.h"
#include <algorithm>

using namespace std;

FilmRepository::FilmRepository()
{
    last_id = 0;
}

FilmRepository::~FilmRepository()
{
    for (int i = films.size() - 1; i >= 0 ; i--)
        delete films[i];
}

Film* FilmRepository::add_new_film(int publisher_id, std::string name, int year, int length, int price, std::string summary, std::string director)
{
    last_id++;
    Film* new_film = new Film(publisher_id, last_id, name, year, length, price, summary, director);
    films.push_back(new_film);
    update_matrix_add_film(new_film->get_id());
    return new_film;
}

Film* FilmRepository::find_film_by_id(int film_id)
{
    for (int i = 0; i < films.size(); i++)
        if(films[i]->get_id() == film_id)
            return films[i];
    throw NotFound();
}

void FilmRepository::update_matrix_buy_film(int bought_films_id, vector<int> films_id)
{
    for (int i = 0; i < films_id.size(); ++i)
        films_matrix[bought_films_id][films_id[i]]++;
}

void FilmRepository::update_matrix_add_film(int film_id)
{
    for (int i = 0; i < films.size(); ++i)
        films_matrix[film_id][films[i]->get_id()] = 0;
}

void FilmRepository::edit_film(int publisher_id, int film_id, std::map<std::string, std::string> edited_options)
{
    if(find_film_by_id(film_id)->get_publisher_id() == publisher_id)
    {
        find_film_by_id(film_id)->edit(edited_options);
        return;
    }
    throw Inaccessibility();
}

void FilmRepository::add_film(Film* film)
{
    if(!check_film_exists(film->get_id()))
        films.push_back(film);
}

bool FilmRepository::check_film_exists(int film_id)
{
    for (int i = 0; i < films.size(); i++)
        if(films[i]->get_id() == film_id)
            return true;
    return false;
}

void FilmRepository::delete_film(int film_id)
{
    for (int i = 0; i < films.size(); i++)
        if(films[i]->get_id() == film_id)
            films.erase(films.begin() + i);
}

int FilmRepository::find_user_id_with_comment_id(int film_id, int comment_id)
{
    return find_film_by_id(film_id)->find_user_id_with_comment_id(comment_id);
}

bool FilmRepository::in_range_film(map<string, string> options, Film* film)
{
    if(options.size() == 0)
        return true;
    bool flag = true;
    for (auto &&option : options)
    {
        if(option.first == NAME && film->get_name() != option.second)
            flag = false;
        if(option.first == "min_rate" && film->get_rate() >= stoi(option.second))
            flag = false;
        if(option.first == "min_year" && film->get_year() >= stoi(option.second))
            flag = false;
        if(option.first == PRICE && film->get_price() >= stoi(option.second))
            flag = false;
        if(option.first == "max_year" && film->get_year() <= stoi(option.second))
            flag = false;
        if(option.first == DIRECTOR && film->get_director() != option.second)
            flag = false;
    } 
    return flag;
}

vector<int> FilmRepository::in_range_films_id(map<string, string> options)
{
    vector<int> films_id_to_show;
    for (int i = 0; i < films.size(); i++)
        if(in_range_film(options, films[i]))
            films_id_to_show.push_back(films[i]->get_id());
    return films_id_to_show;
}

void FilmRepository::show_films(map<string, string> options)
{
    cout << "#. Film Id | Film Name | Film Length | Film price | Rate | Production Year | Film Director\n";
    vector<int> films_id_to_show = in_range_films_id(options);
    sort(films_id_to_show.begin(), films_id_to_show.end());
    for (int i = 0; i < films_id_to_show.size(); i++)
        cout << i + 1 << ". " << find_film_by_id(films_id_to_show[i])->show() << "\n";
}

void FilmRepository::show_film_details(int film_id)
{
     cout << find_film_by_id(film_id)->show_details();
}

vector<pair<int, int>> FilmRepository::sort_pairs_by_weight(int film_id)
{
    vector<pair<int, int>> sort_by_weight;
    for (auto& related_films: films_matrix[film_id])
        sort_by_weight.push_back(pair<int, int> (related_films.second, related_films.first));
    sort(sort_by_weight.begin(), sort_by_weight.end());
    return sort_by_weight;
}

bool FilmRepository::existed(vector<int> bought_films_id, int id)
{
    for (int i = 0; i < bought_films_id.size(); i++)
        if(bought_films_id[i] == id)
            return true;
    return false;
}

void FilmRepository::show_recommend_film(vector<int> bought_films_id, int film_id)
{
    cout << "Recommendation Film\n#. Film Id | Film Name | Film Length | Film Director\n";
    int counter = 1;
    vector<pair<int, int>> sorted_by_weight = sort_pairs_by_weight(film_id);
    for (int i = 0; i < sorted_by_weight.size(); i++)
    {
        if(!existed(bought_films_id, sorted_by_weight[i].second) && counter <= 4 && sorted_by_weight[i].second != film_id)
        {
            cout << counter << ". "  << find_film_by_id(sorted_by_weight[i].second)->show_recommend();
            counter++;
        }
    }
}

vector<int> FilmRepository::get_films_id()
{
    vector<int> films_id;
    for (int i = 0; i < films.size(); i++)
        films_id.push_back(films[i]->get_id());
    return films_id;
}