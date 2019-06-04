#include "show.hpp"
#include "../Assignment7/exceptions.h"
#include <iostream>
#include <string>
#include <map>
#include <sstream>

using namespace std;

Response* Show::show_films(int method, vector<vector<string>> films)
{
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    ostringstream body;
    body
        << "<html>" << endl
        << "<head>" << endl
        << "    <link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css'>" << endl
        << "</head>" << endl
        << "<body>" << endl
        << "     <nav class='navbar navbar-expand-sm bg-dark navbar-dark fixed-top'>" << endl
        << "         <ul class='navbar-nav'>" << endl
        << "             <form action='/logout' method='POST'>" << endl
        << "                 <button class='btn btn-danger' type='submit'>Logout</button>" << endl
        << "             </form>" << endl
        << "         </ul>" << endl;
    if(method == PUBLISHED)
    {
        body
        << "         <ul class='navbar-nav'>" << endl
        << "             <form action='/add_film' method='GET'>" << endl
        << "                 <button class='btn btn-warning' type='submit'>Add film</button>" << endl
        << "             </form>" << endl
        << "         </ul>" << endl;
    }
    if(method == USER)
    {        
        body
        << "         <ul class='navbar-nav'>" << endl
        << "                 <form action='/profile' method='GET'>" << endl
        << "                     <button class='btn btn-warning' type='submit'>Profile</button>" << endl
        << "                 </form>" << endl
        << "         </ul>" << endl;
    }
    body
        << "    </nav>" << endl
        <<"    <form action='/search' method='POST'>" << endl
        <<"        <div class='input-group' style='padding-left: 30%; padding-top: 10%; max-width: 70%;'>" << endl
        <<"            <span class='input-group-btn'>" << endl
        <<"                <button class='btn btn-default' type='submit' style='background-color: blue; color: white'>Go</button>" << endl
        <<"            </span>" << endl
        <<"            <input type='text' class='form-control' id='publisher' name='director' placeholder='director'>" << endl
        <<"        </div>" << endl
        <<"    </form>" << endl;
    body    
        <<"    <div class='container'>" << endl;
    if(method == PUBLISHED)
    {
        body
            <<"        <h2>Published Films</h2>" << endl;
    }
    if(method == USER)
    {
        body
            <<"        <h2>All Films</h2>" << endl;
    }
    if(method == PROFILE)
    {
        body
            <<"        <h2>Bought Films</h2>" << endl;
    }
    body
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
        <<"            <tbody>" << endl;
    for (int i = 0; i < films.size(); i++)
    {
        body
            <<"                <tr>" << endl
            <<"                    <td>" << films[i][0] << "</td>" << endl
            <<"                    <td>" << endl
            <<"                        <form action='/details' method='POST'>" << endl
            <<"                            <div class='input-group'>" <<endl
            <<"                                <span class='input-group-btn'>" << endl
            <<"                                     <input class='btn btn' type='submit' style='color: white' value='" << films[i][i] << "'></button>" << endl
            <<"                                </span>"
            <<"                                <input type='hidden' class='form-control' id='delete_film' name='film_id' value='" << films[i][0] << "'>" << endl
            <<"                            </div>" << endl
            <<"                        </form>" << endl              
            << "                   </td>" << endl
            <<"                    <td>" << films[i][2] << "</td>" << endl
            <<"                    <td>" << films[i][3] << "</td>" << endl
            <<"                    <td>" << films[i][4] << "</td>" << endl
            <<"                    <td>" << films[i][5] << "</td>" << endl
            <<"                    <td>" << films[i][6] << "</td>" << endl;
        if(method == PUBLISHED)
        {
            body
                <<"                    <td>" << endl
                <<"                        <form action='/delete_film' method='POST'>" << endl
                <<"                            <div class='input-group'>" <<endl
                <<"                                <span class='input-group-btn'>" << endl
                <<"                                        <button class='btn btn-warning' type='submit'>DELETE</button>" << endl
                <<"                                    </span>"
                <<"                                <input type='hidden' class='form-control' id='delete_film' name='film_id' value='" << films[i][0] << "'>" << endl
                <<"                            </div>" << endl
                <<"                        </form>" << endl
                <<"                    </td>" << endl;
        }
        body
            <<"                </tr>" << endl;
    }    
    body
        <<"            </tbody>" << endl
        <<"        </table>" << endl
        <<"    </div>" << endl;
    if(method == PROFILE)
    {        
        body
            <<"    <form action='/money' method='POST'>" << endl
            <<"        <div class='input-group' style='padding-left: 30%; padding-top: 20%; max-width: 70%;'>" << endl
            <<"            <span class='input-group-btn'>" << endl
            <<"                <button class='btn btn-default' type='submit' style='background-color: yellow; color: white'>Increase</button>" << endl
            <<"            </span>" << endl
            <<"            <input type='number' class='form-control' id='money' name='money' placeholder='money'>" << endl
            <<"        </div>" << endl
            <<"    </form>" << endl;
    }
    body
        <<"</body>" << endl
        <<"</html>" << endl;
    res->setBody(body.str());
    return res;
}
