#ifndef COMMENT_REPOS_H
#define COMMENT_REPOS_H

#include "comment.h"
#include <vector>

class CommentRepository
{
public:
    CommentRepository();
    Comment* find_comment_by_id(int commetn_id);
    int find_user_id_with_comment_id(int comment_id);
    int find_comment_index(int comment_id);
    void delete_comment(int comment_id);
    void add_comment(std::string content, int user_id);
    std::string show_comments();
private:
    int last_id;
    std::vector<Comment*> comments;
};

#endif