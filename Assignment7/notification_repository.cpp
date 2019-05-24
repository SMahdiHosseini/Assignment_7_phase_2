
#include "notification_repository.h"

using namespace std;

void NotificationRepository::give_notification(Notification notification)
{
    notifications.push_back(notification);
}

void NotificationRepository::show_unread_notifications()
{
    cout << "#. Notification Message\n";
    for (int i = notifications.size() - 1; i >= 0; i--)
    {
        if(!notifications[i].get_read())
        {
            cout << to_string(notifications.size() - i) << ". ";
            notifications[i].read_massage();
            notifications[i].show_massage();
        }
    }
}

void NotificationRepository::show_notifications(int limit)
{
    cout << "#. Notification Message\n";
    for (int i = notifications.size() - 1; i >= 0; i--)
    {
        if(notifications[i].get_read() && limit > 0)
        {            
            cout << to_string(notifications.size() - i) << ". ";
            notifications[i].show_massage();
            limit--;
        }
    }
}