#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <vector>
#include "definitions.h"
#include "network.h"
#include "validity.h"

typedef std::vector<std::string> string_list;

class CommandHandler
{
public:
    CommandHandler();
    ~CommandHandler();
    string_list split_string(std::string input);
    void reply_comment();
    void follow();
    void run();
    void edit_film();
    void increase_money();
    void rate_film();
    void buy_film();
    void detect_instruction_methode();
    void post_methode_instructions();
    void get_methode_instructions();
    void put_methode_instructions();
    void delete_methode_instructions();
    void signup();
    void login();
    void add_comment();
    void add_film();
    void delete_film();
    void delete_comment();
    void show_films(std::string type);
    void show_notifications();
    int find_optional_index(std::string key);
    int find_index(std::string key);
    bool check_publisher(std::string publisher);
    bool show_details();
    bool show_all(std::map<std::string, std::string> elements, std::string type);
private:
    Network* network;
    string_list input;
    Validity valid;
};

#endif