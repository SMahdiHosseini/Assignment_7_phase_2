#include "../Assignment7/network.h"
#include "my_server.hpp"
#include "handlers.hpp"
#include "details_handler.hpp"
#include "login_handler.hpp"
#include "signup_handler.hpp"
#include "profile_handler.hpp"
#include "film_handler.hpp"
#include "increase_handler.hpp"
#include "delete_handler.hpp"
#include "search_handler.hpp"
#include "buy_handler.hpp"
#include "home_handler.hpp"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    Network* network = new Network();

    MyServer server(argc > 1 ? atoi(argv[1]) : 5000);
    try
    {
        server.setNotFoundErrPage("static/404.html");

        server.get("/1.jpg", new ShowImage("static/1.jpg"));
        server.get("/", new ShowPage("static/home.html"));
    
        server.get("/login", new ShowPage("static/home.html"));
        server.post("/login", new LoginHandler(network));        

        server.get("/signup", new ShowPage("static/signup.html"));
        server.post("/signup", new SignupHandler(network));

        server.get("/add_film", new ShowPage("static/add_film.html"));
        server.post("/add_film", new FilmHandler(network));

        server.get("/profile", new ProfileHandler(network));

        server.post("/money", new IncreaseHandler(network));

        server.post("/search", new SearchHandler(network));

        server.post("/details", new DetailsHandler(network));

        server.post("/delete", new DeleteHandler(network));

        server.post("/buy", new BuyHandler(network));

        server.post("/logout", new LogoutHandler(network));

        server.post("/home", new HomeHandler(network));

        server.run();
    }
    catch(MyServer::Exception e)
    {
        cerr << e.getMessage() << endl;
    }
}