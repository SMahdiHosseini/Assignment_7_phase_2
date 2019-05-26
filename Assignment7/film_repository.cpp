#include "film_repository.h"
#include "exceptions.h"
#include "definitions.h"
#include <algorithm>

using namespace std;

FilmRepository::FilmRepository()
{
}

Film* FilmRepository::find_film_by_id(int film_id)
{
    for (int i = 0; i < films.size(); i++)
        if(films[i]->get_id() == film_id)
            return films[i];
    throw NotFound();
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

vector<int> FilmRepository::get_films_id()
{
    vector<int> films_id;
    for (int i = 0; i < films.size(); i++)
        films_id.push_back(films[i]->get_id());
    return films_id;
}