#ifndef COMMENT_H
#define COMMENT_H

#include <iostream>
#include "notification.h"

class Comment
{
public:
    Comment(int _id, std::string _content, int _user_id);
    int get_id();
    int get_user_id();
    void reply_content(std::string content);
    std::string get_content();
    std::string get_reply();
private:
    int id;
    int user_id;
    std::string content;
    std::string reply;
};

#endif