#incldue "network_film_repository.h"

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