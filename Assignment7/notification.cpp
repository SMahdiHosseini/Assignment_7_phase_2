#include "notification.h"

using namespace std;

Notification::Notification(string _massage)
{
    massage = _massage;
    read = false;
}

void Notification::read_massage()
{
    read = true;
}

void Notification::show_massage()
{
    cout << massage << endl;
}

bool Notification::get_read()
{
    return read;
}