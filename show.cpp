#include "show.hpp"
#include "../Assignment7/exceptions.h"
#include <iostream>
#include <string>
#include <map>
#include <sstream>

using namespace std;


Show::Show()
{
}

string Show::set_nav(int method)
{        
    ostringstream nav_bar;
    nav_bar
        << "<nav class='navbar navbar-expand-sm bg-dark navbar-dark fixed-top'>" << endl
        << "    <ul class='navbar-nav'>" << endl
        << "        <form action='/logout' method='POST'>" << endl
        << "            <button class='btn btn-danger' type='submit'>Logout</button>" << endl
        << "        </form>" << endl
        << "    </ul>" << endl;
    if(method == PUBLISHED)
    {
        nav_bar
        << "    <ul class='navbar-nav'>" << endl
        << "        <form action='/add_film' method='GET'>" << endl
        << "            <button class='btn btn-warning' type='submit'>Add film</button>" << endl
        << "        </form>" << endl
        << "    </ul>" << endl;
    }
    if(method == USER)
    {        
        nav_bar
        << "    <ul class='navbar-nav'>" << endl
        << "            <form action='/profile' method='GET'>" << endl
        << "                <button class='btn btn-warning' type='submit'>Profile</button>" << endl
        << "            </form>" << endl
        << "    </ul>" << endl;
    }
    nav_bar
        << "</nav>" << endl;
    return nav_bar.str();
}

string Show::set_table_title(int method)
{
    ostringstream head;
    if(method == PUBLISHED)
    {
        head
            << "<h2>Published Films</h2>" << endl;
    }
    if(method == USER)
    {
        head
            << "<h2>All Films</h2>" << endl;
    }
    if(method == PROFILE)
    {
        head
            << "<h2>Bought Films</h2>" << endl;
    }
    return head.str();
}

string Show::set_table_body(int method, vector<string> film)
{      
    ostringstream body;
    body
        << "<tr>" << endl
        << "    <td>" << film[0] << "</td>" << endl
        << "    <td>" << endl
        << "        <form action='/details' method='POST'>" << endl
        << "            <div class='input-group'>" <<endl
        << "                <span class='input-group-btn'>" << endl
        << "                     <input class='btn btn' type='submit' style='color: white' value='" << film[1] << "'></button>" << endl
        << "                </span>"
        << "                <input type='hidden' class='form-control' id='delete_film' name='film_id' value='" << film[0] << "'>" << endl
        << "            </div>" << endl
        << "        </form>" << endl              
        << "    </td>" << endl
        << "    <td>" << film[2] << "</td>" << endl
        << "    <td>" << film[3] << "</td>" << endl
        << "    <td>" << film[4] << "</td>" << endl
        << "    <td>" << film[5] << "</td>" << endl
        << "    <td>" << film[6] << "</td>" << endl;
    if(method == PUBLISHED)
    {
        body
            << "    <td>" << endl
            << "        <form action='/delete_film' method='POST'>" << endl
            << "            <div class='input-group'>" <<endl
            << "                <span class='input-group-btn'>" << endl
            << "                        <button class='btn btn-warning' type='submit'>DELETE</button>" << endl
            << "                    </span>"
            << "                <input type='hidden' class='form-control' id='delete_film' name='film_id' value='" << film[0] << "'>" << endl
            << "            </div>" << endl
            << "        </form>" << endl
            << "    </td>" << endl;
    }
    body
        << "</tr>" << endl;
    return body.str();
}

string Show::increase_money_form()
{
    ostringstream body;
    body
        << "<form action='/money' method='POST'>" << endl
        << "    <div class='input-group' style='padding-left: 30%; padding-top: 20%; max-width: 70%;'>" << endl
        << "        <span class='input-group-btn'>" << endl
        << "            <button class='btn btn-default' type='submit' style='background-color: yellow; color: white'>Increase</button>" << endl
        << "        </span>" << endl
        << "        <input type='number' class='form-control' id='money' name='money' placeholder='money'>" << endl
        << "    </div>" << endl
        << "</form>" << endl;
    return body.str();
}

string Show::serach_form()
{
    ostringstream body;
    body
        << "<form action='/search' method='POST'>" << endl
        << "    <div class='input-group' style='padding-left: 30%; padding-top: 10%; max-width: 70%;'>" << endl
        << "        <span class='input-group-btn'>" << endl
        << "            <button class='btn btn-default' type='submit' style='background-color: blue; color: white'>Go</button>" << endl
        << "        </span>" << endl
        << "        <input type='text' class='form-control' id='publisher' name='director' placeholder='director'>" << endl
        << "    </div>" << endl
        << "</form>" << endl;
    return body.str();
}

string Show::table_header()
{
    ostringstream header;
    header
        << "<thead>" << endl
        << "    <tr>" << endl
        << "        <th>Film Id</td>" << endl                           
        << "        <th>Name</th>" << endl
        << "        <th>Price</th>" << endl
        << "        <th>Year</th>" << endl
        << "        <th>Lenght</th>" << endl
        << "        <th>Rate</th>" << endl
        << "        <th>Director</th>" << endl
        << "        <th>Delete Film</th>" << endl
        << "    </tr>" << endl
        << "</thead>" << endl;
    return header.str();
}

string Show::header()
{
    ostringstream head;
    head
        << "<head>" << endl
        << "    <link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css'>" << endl
        << "</head>" << endl;
    return head.str();
}

string Show::table(int method, vector<vector<string>> films)
{
    ostringstream table;
    table << "<div class='container'>" << endl;
    table << set_table_title(method);
    table << "  <table class='table table-dark table-striped'>" << endl;
    table << table_header();
    table << "      <tbody>" << endl;
    for (int i = 0; i < films.size(); i++)
        table << set_table_body(method, films[i]);    
    table << "      </tbody>" << endl;
    table << "  </table>" << endl;
    table << "</div>" << endl;
    return table.str();
}

Response* Show::show_films(int method, vector<vector<string>> films)
{
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    ostringstream body;
    body << "<html>" << endl;
    body << header();
    body << "<body>" << endl;
    body << set_nav(method);
    body << serach_form();
    body << table(method, films);
    if(method == PROFILE)
        body << increase_money_form();
    body <<"</body>" << endl;
    body <<"</html>" << endl;
    res->setBody(body.str());
    return res;
}
