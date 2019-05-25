#include "command_handler.h"
#include <iostream>

using namespace std;
int main()
{
    CommandHandler* netflix = new CommandHandler();
    netflix->run();
    // netflix->~CommandHandler();
}