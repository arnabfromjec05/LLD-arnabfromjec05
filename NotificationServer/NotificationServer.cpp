

#include <iostream>
#include <map>
using namespace std;

enum NotificationSendStatus
{
    OUTSTANDING,
    SENT,
    FAILED
};

class Notification
{
    string notificationId;
    long currentBTCPrice;
    long marketTradeVolume;
    long intradayHighPrice;
    long marketCap;
    NotificationSendStatus status;

public:
    Notification(string notificationId, long currentBTCPrice, long marketTradeVolume,
                 long intradayHighPrice, long marketCap)
    {
        this->notificationId = notificationId;
        this->currentBTCPrice = currentBTCPrice;
        this->marketTradeVolume = marketTradeVolume;
        this->intradayHighPrice = intradayHighPrice;
        this->marketCap = marketCap;
        this->status = NotificationSendStatus::OUTSTANDING;
    }

    long getCurrentBTCPrice()
    {
        return currentBTCPrice;
    }

    long getMarketTradeVolume()
    {
        return marketTradeVolume;
    }

    long getIntradayHighPrice()
    {
        return intradayHighPrice;
    }

    long getMarketCap()
    {
        return marketCap;
    }

    NotificationSendStatus getNotificationSendState()
    {
        return status;
    }

    void setNotificationSendState(NotificationSendStatus status)
    {
        this->status = status;
    }

    void printNotification()
    {
        cout << "NotificationId: " << notificationId
             << " CurrentBTCPrice: " << currentBTCPrice
             << " MarketTradeVolume: " << marketTradeVolume
             << " IntradayHighPrice: " << intradayHighPrice
             << " MarketCap: " << marketCap
             << " Notification Status: " << status << endl;
    }
};

// Any new intimation provider should implement this interface
class IIntimationService
{
public:
    virtual void sendNotification(Notification *notification,
                                  NotificationSendStatus finalState) = 0;
};

class EmailService : public IIntimationService
{
public:
    void sendNotification(Notification *notification,
                          NotificationSendStatus finalState)
    {
        // Mock send notification behavior to final state
        notification->setNotificationSendState(finalState);
    }
};

class NotificationServer
{
    map<string, Notification *> notifications;
    IIntimationService *intimationService;

public:
    NotificationServer()
    {
        intimationService = new EmailService();
    }

    void createNotification(string notificationId, long currentBTCPrice, long marketTradeVolume,
                            long intradayHighPrice, long marketCap)
    {

        // Assumtion: notificationId is unique and not seen before
        Notification *notification = new Notification(
            notificationId,
            currentBTCPrice,
            marketTradeVolume,
            intradayHighPrice,
            marketCap);

        notifications[notificationId] = notification;
    }

    void listNotifications(NotificationSendStatus state)
    {
        cout << "Listing all notifications in state: " << state << "---->" << endl;
        for (auto itr = notifications.begin(); itr != notifications.end(); itr++)
        {
            if (itr->second->getNotificationSendState() == state)
            {
                itr->second->printNotification();
            }
        }
    }

    void sendNotification(string notificationId, NotificationSendStatus finalState)
    {
        if (notifications.find(notificationId) == notifications.end())
        {
            cout << "Notification is not found" << endl;
            return;
        }
        Notification *notification = notifications[notificationId];
        intimationService->sendNotification(notification, finalState);
    }

    bool deleteNotification(string notificationId)
    {
        if (notifications.find(notificationId) == notifications.end())
        {
            cout << "Notification is not found" << endl;
            return false;
        }
        notifications.erase(notificationId);
        return true;
    }
};

// class ResponseBody {
// 	int code;
// 	string message;
// public:
// 	ResponseBody(int code, string message) {
// 		this->code = code;
// 		this->message = message;
// 	}
// }

int main()
{
    NotificationServer *service = new NotificationServer();
    service->createNotification("1", 10, 10, 10, 10);
    service->listNotifications(NotificationSendStatus::OUTSTANDING);
    service->createNotification("2", 20, 20, 20, 20);
    service->listNotifications(NotificationSendStatus::OUTSTANDING);
    service->createNotification("3", 30, 30, 30, 30);
    service->listNotifications(NotificationSendStatus::OUTSTANDING);

    service->sendNotification("1", NotificationSendStatus::SENT);
    service->sendNotification("2", NotificationSendStatus::FAILED);
    service->listNotifications(NotificationSendStatus::OUTSTANDING);
    service->listNotifications(NotificationSendStatus::SENT);
    service->listNotifications(NotificationSendStatus::FAILED);

    service->deleteNotification("2");
    service->listNotifications(NotificationSendStatus::FAILED); // Empty
    service->deleteNotification("2");                           // Notification not present, shouldn't succeed
    return 0;
}