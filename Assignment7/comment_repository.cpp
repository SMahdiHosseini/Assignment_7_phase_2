#include "comment_repository.h"
#include "exceptions.h"

using namespace std;

CommentRepository::CommentRepository()
{
    last_id = 0;
}

Comment* CommentRepository::find_comment_by_id(int comment_id)
{
    for (int i = 0; i < comments.size(); i++)
        if(comments[i]->get_id() == comment_id)
            return comments[i];
    throw Inaccessibility();
}

int CommentRepository::find_comment_index(int comment_id)
{
    for (int i = 0; i < comments.size(); i++)
        if(comments[i]->get_id() == comment_id)
            return i;
    throw Inaccessibility();
}

void CommentRepository::delete_comment(int comment_id)
{
    comments.erase(comments.begin() + find_comment_index(comment_id));
}

void  CommentRepository::add_comment(string content, int user_id)
{
    last_id++;
    Comment* new_comment = new Comment(last_id, content, user_id);
    comments.push_back(new_comment);
}

int CommentRepository::find_user_id_with_comment_id(int comment_id)
{
    return find_comment_by_id(comment_id)->get_user_id();
}

string CommentRepository::show_comments()
{
    string result = "\nComments\n\n";
    for (int i = 0; i < comments.size(); i++)
    {
        result += to_string(comments[i]->get_id()) + ". " + comments[i]->get_content() + "\n";
        result += to_string(comments[i]->get_id()) + ".1. " + comments[i]->get_reply() + "\n";
    }
    return result;
}