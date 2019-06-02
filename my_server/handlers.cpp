#include "handlers.hpp"
#include "../Assignment7/exceptions.h"
#include <iostream>
#include <string>
#include <map>
#include <sstream>

using namespace std;

LogoutHandler::LogoutHandler(Network* _network) : network(_network)
{
}

Response* LogoutHandler::callback(Request* req)
{
    network->logout();
    return Response::redirect("/");
}

LoginHandler::LoginHandler(Network* _network) : show(_network)
{
}

Response* LoginHandler::callback(Request* req)
{
    map<string, string> elements;
    elements["username"]= req->getBodyParam("username");
    elements["password"] = req->getBodyParam("password");
    if (valid.login_validity(elements))
    {
        try
        {
            show.network->login(elements["username"], elements["password"]);
            return show.show_films();
        }
        catch(...)
        {
            throw Server::Exception("Bad request");
        }
    }
    else
        throw Server::Exception("Bad request");        
}

Response* Show::show_films()
{
    map<string, string> options;
    vector<vector<string>> films;
    if(network->find_logged_in_user()->check_publsher() == true)
        films = network->show_published_film(options);
    else
    {
        options["price"] = network->find_logged_in_user()->get_money();
        films = network->search(options);
    }
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    ostringstream body;
    body
        <<"<html>" << endl
        <<"<head>" << endl
        <<"    <link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/css/bootstrap.min.css'>" << endl
        <<"</head>" << endl
        <<"<body>" << endl
        << "    <nav class='navbar navbar-expand-sm bg-dark navbar-dark fixed-top'>" << endl
        << "        <ul class='navbar-nav'>" << endl
        << "            <li class='nav-item'>" << endl
        << "                <form action='/logout' method='POST'><button class='btn btn-danger' type='submit'>Logout</button></form>" << endl
        << "            </li>" << endl
        << "        </ul>" << endl
        << "    </nav>" << endl
        <<"    <form action='/home' method='POST'>" << endl
        <<"        <div class='input-group' style='padding-left: 30%; padding-top: 5%; max-width: 70%;'>" << endl
        <<"            <span class='input-group-btn'>" << endl
        <<"                <button class='btn btn-default' type='submit' style='background-color: blue; color: white'>Go</button>" << endl
        <<"            </span>" << endl
        <<"            <input type='text' class='form-control' id='publisher' name='director' placeholder='director'>" << endl
        <<"        </div>" << endl
        <<"    </form>" << endl
        <<"    <div class='container'>" << endl
        <<"        <h2>Published Films</h2>" << endl
        <<"        <table class='table table-dark table-striped'>" << endl
        <<"            <thead>" << endl
        <<"                <tr>" << endl
        <<"                    <th>Film Id</td>" << endl                           
        <<"                    <th>Name</th>" << endl
        <<"                    <th>Price</th>" << endl
        <<"                    <th>Year</th>" << endl
        <<"                    <th>Lenght</th>" << endl
        <<"                    <th>Rate</th>" << endl
        <<"                    <th>Director</th>" << endl
        <<"                    <th>Delete Film</th>" << endl
        <<"                </tr>" << endl
        <<"            </thead>" << endl
        <<"            <tbody>" << endl
        <<"                <tr>" << endl;
        for (int i = 0; i < films.size(); i++)
        {
            body
                <<"                    <td>" << films[i][0] << "</td>" << endl
                <<"                    <td>" << films[i][1] << "</td>" << endl
                <<"                    <td>" << films[i][2] << "</td>" << endl
                <<"                    <td>" << films[i][3] << "</td>" << endl
                <<"                    <td>" << films[i][4] << "</td>" << endl
                <<"                    <td>" << films[i][5] << "</td>" << endl
                <<"                    <td>" << films[i][6] << "</td>" << endl
                <<"                    <td>" << endl
                <<"                        <form action='/delete_film' method='POST'><button class='btn btn-warning' type='submit'>DELETE</button></form>" << endl
                <<"                    </td>" << endl;
        }
    body
        <<"                </tr>" << endl
        <<"            </tbody>" << endl
        <<"        </table>" << endl
        <<"    </div>" << endl
        <<"</body>" << endl
        <<"</html>" << endl;
    res->setBody(body.str());
    return res;
}


SignupHandler::SignupHandler(Network* _network) : LoginHandler(_network)
{
}

Response* SignupHandler::callback(Request* req)
{
    map<string, string> elements;
    elements["username"]= req->getBodyParam("username");
    elements["password"] = req->getBodyParam("password");
    elements["email"] = req->getBodyParam("email");
    elements["age"] = req->getBodyParam("age");
    elements["publisher"] = req->getBodyParam("publisher");
    string retry_pass = req->getBodyParam("retry_password");
    if(valid.signup_validity(elements) && retry_pass == elements["password"])
    {   
        try
        {
            show.network->signup(elements["email"], elements["username"], elements["password"], 
                        stoi(elements["age"]), valid.check_publisher(elements["publisher"]));
            return show.show_films();
        }
        catch(...)
        {
            throw Server::Exception("Bad request");    
        }
    }
    else
        throw Server::Exception("Bad request");
}

FilmHandler::FilmHandler(Network* _network) : show(_network)
{
}

Response* FilmHandler::callback(Request* req)
{
    map<string, string> elements;
    elements["name"]= req->getBodyParam("name");
    elements["director"] = req->getBodyParam("director");
    elements["length"] = req->getBodyParam("length");
    elements["summary"] = req->getBodyParam("summary");
    elements["rate"] = req->getBodyParam("rate");
    elements["year"] = req->getBodyParam("year");
    elements["rate"] = req->getBodyParam("rate");
    elements["price"] = req->getBodyParam("price");
    if(valid.add_film_validity(elements))
    {   
        try
        {
            show.network->add_film(elements["name"], stoi(elements["year"]), stoi(elements["length"]), 
                                stoi(elements["price"]), elements["summary"], elements["deirector"]);
            return show.show_films();
        }
        catch(...)
        {
            throw Server::Exception("Bad request");    
        }
    }
    else
        throw Server::Exception("Bad request");
}