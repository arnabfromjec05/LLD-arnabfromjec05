#include <iostream>
#include <map>
#include <set>
using namespace std;

class User
{
    string userId; // phoneNum/userId etc
    string name;

public:
    User(string userId, string name)
    {
        this->userId = userId;
        this->name = name;
    }

    string getUserId()
    {
        return userId;
    }

    string getName()
    {
        return name;
    }

    void printUser()
    {
        cout << "UserId: " << userId << " Name: " << name << endl;
    }
};

class Message
{
    User *sender;
    User *receiver;
    string content;
    long timestamp;

public:
    Message(User *sender, User *receiver, string content, long timestamp)
    {
        this->sender = sender;
        this->receiver = receiver;
        this->content = content;
        this->timestamp = timestamp;
    }

    User *getSender()
    {
        return sender;
    }

    User *getReceiver()
    {
        return receiver;
    }

    string getContent()
    {
        return content;
    }

    long getTimestamp()
    {
        return timestamp;
    }

    // dummy message send behavior
    void sendMessage()
    {
        cout << "[MessageSent] Sender: " << sender->getUserId()
             << " to Receiver: " << receiver->getUserId()
             << " = " << content << endl;
    }

    void printMessage()
    {
        cout << "[Convo] Sender: " << sender->getUserId()
             << " to Receiver: " << receiver->getUserId() << " : "
             << content
             << " Timestamp: " << timestamp << endl;
    }
};

class ChatService
{
    map<string, User *> users;
    vector<Message *> messages;

public:
    // Todo: add new users to the chat system
    void addUser(string userId, string name)
    {

        if (users.find(userId) == users.end())
        {
            User *user = new User(userId, name);
            users[userId] = user;
            return;
        }
        cout << "User is already present in the system" << endl;
    }

    // Todo: sends a message
    void sendMessage(string senderId, string receiverId, string content,
                     long timestamp)
    {

        if (users.find(senderId) == users.end() || users.find(receiverId) == users.end())
        {
            cout << "Either sender or receiver not found" << endl;
        }

        User *sender = users[senderId];
        User *receiver = users[receiverId];
        Message *message = new Message(sender, receiver, content, timestamp);
        message->sendMessage();
        messages.push_back(message);
    }

    // Todo: print all convo happened between sender & reveiver
    void printConversation(string senderId, string receiverId)
    {
        if (users.find(senderId) == users.end() || users.find(receiverId) == users.end())
        {
            cout << "Either sender or receiver not found" << endl;
        }

        for (int i = 0; i < messages.size(); i++)
        {
            Message *message = messages[i];
            if (senderId == message->getSender()->getUserId() && receiverId == message->getReceiver()->getUserId())
            {
                message->printMessage();
            }
        }
    }
};

int main()
{

#ifndef ONLINE_JUDGE
    freopen("input1.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
#endif

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // std::cout << std::fixed << std::setprecision(9);

    ChatService *service = new ChatService();
    service->addUser("user1", "X");
    service->addUser("user2", "Y");
    service->addUser("user3", "Z");

    service->sendMessage("user1", "user2", "Hello!", 1);
    service->sendMessage("user2", "user3", "Hello!", 2);
    service->sendMessage("user2", "user1", "Hi!", 3);
    service->sendMessage("user2", "user3", "There!", 4);
    service->sendMessage("user2", "user4", "akdaslkd", 5);

    service->printConversation("user2", "user3");

    return 0;
}