#include "comment.h"

using namespace std;

Comment::Comment(int _id, string _content, int _user_id)
{
    id = _id;
    content = _content;
    user_id = _user_id;
}

int Comment::get_id()
{
    return id;
}

void Comment::reply_content(string _content)
{
    reply = _content;
}

int Comment::get_user_id()
{
    return user_id;
}

string Comment::get_content()
{
    return content;
}
string Comment::get_reply()
{
    return reply;
}