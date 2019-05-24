#ifndef NOTIF_REPOS_H
#define NOTIF_REPOS_H

#include "notification.h"
#include <vector>

class NotificationRepository
{
public:
    NotificationRepository() {};
    void give_notification(Notification notification);
    void show_unread_notifications();
	void show_notifications(int limit);
private:
    std::vector<Notification> notifications;
};

#endif