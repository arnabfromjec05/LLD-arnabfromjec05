#include<iostream>
#include<algorithm>
#include<vector>
#include<map>

using namespace std;

enum Cadence {
    Weekly = 7,
    Monthly = 30,
    Quarterly = 90
};

enum SipStatus {
    Active,
    Paused,
    Stopped
};

class MutualFund {
    public:
        string id;
        string name;
        double currentVal;

        MutualFund(string id, string name, double currentVal) {
            this->id = id;
            this->name = name;
            this->currentVal = currentVal;
        }

        // Called whenever MF value is updated in the exchange
        void updateVal(double latestVal) {
            currentVal = latestVal;
        }

        void print() {
            cout<<"Mutual fund: "
                <<this->id<<", "
                <<this->name<<", "
                <<currentVal<<endl;
        }
};

class Sip {

    map<SipStatus, string> sipStatusMapper = {
        {SipStatus::Active, "Active"},
        {SipStatus::Paused, "Paused"},
        {SipStatus::Stopped, "Stopped"},
    };

    public:
        string id;
        string userId;
        string mutualFundId;
        double amount;
        Cadence cadence;
        int createdTime;
        SipStatus status;

        Sip(
            string id,
            string userId,
            string fundId,
            double amount,
            Cadence cadence,
            int createdTime)
        {
            this->id = id;
            this->userId = userId;
            this->mutualFundId = fundId;
            this->amount = amount;
            this->cadence = cadence;
            this->createdTime = createdTime;
            this->status = Active;
        }

        bool shouldExecute(int currentDay) {

            if (status != Active)
                return false;

            return ((currentDay - createdTime) % cadence == 0);
        }

        void print() {
            cout << "SipId: " << id
                << " Fund: " << mutualFundId
                << " Amount: " << amount
                << " Status: " << sipStatusMapper[status]
                << endl;
        }
};

class User {
    public:
        string id;
        string name;
        vector<Sip*> sips;

        User(string id, string name) {
            this->id = id;
            this->name = name;
        }

        void addSip(Sip* sip) {
            sips.push_back(sip);
        }
};

class FundService {

    map<string, MutualFund*> funds;

    public:
        
        MutualFund* getMutualFund(string id) {
            auto itr = funds.find(id);
            if (itr == funds.end()) {
                return nullptr;
            }
            return itr->second;
        }

        vector<MutualFund*> getAllMutualFunds() {
            vector<MutualFund*> res;
            for (auto& kv: funds) {
                res.push_back(kv.second);
            }
            return res;
        }

        bool addMutualFund(string id, string name, double val) {
            if (funds.find(id) != funds.end()) {
                return false;
            }
            MutualFund* fund = new MutualFund(id, name, val);
            funds[id] = fund;
            return true;
        }

        bool updateMutualValue(string id, double val) {
            auto itr = funds.find(id);
            if (itr == funds.end()) {
                return false;
            }
            itr->second->updateVal(val);
            return true;
        }
};

class UserService {

    map<string, User*> users;

public:

    bool addUser(string id, string name) {
        if (users.find(id) != users.end())
            return false;

        users[id] = new User(id, name);
        return true;
    }

    User* getUser(string id) {
        if (users.find(id) == users.end())
            return nullptr;

        return users[id];
    }

    vector<User*> getAllUsers() {
        vector<User*> res;

        for (auto& kv : users)
            res.push_back(kv.second);

        return res;
    }
};

// Main service catering to user
class SipService {

    FundService* fundService;
    UserService* userService;

    map<string, Sip*> sipRegistry;
    int sipCounter = 1;

    public:

        SipService(FundService* fundService, UserService* userService) {
            this->fundService = fundService;
            this->userService = userService;
        }

        // Print all mutual funds available
        void getMutualFunds() {
            for(auto& fund: fundService->getAllMutualFunds()) {
                fund->print();
            }
        }

        // Setup new sip
        string setupSip(
            string userId,
            string fundId,
            double amount,
            Cadence cadence,
            int startDay)
        {
            User* user = userService->getUser(userId);
            MutualFund* fund = fundService->getMutualFund(fundId);

            if (!user || !fund) {
                return "";
            }

            string sipId = "SIP" + to_string(sipCounter++);
            Sip* sip = new Sip(sipId, userId, fundId, amount, cadence, startDay);
            user->addSip(sip);
            sipRegistry[sipId] = sip;

            return sipId;
        }

        // Display sips of given user
        void displaySips(string userId) {
            User* user = userService->getUser(userId);
            if (!user) return;

            cout << "SIPs for user " << user->name << endl;
            for (auto sip : user->sips)
                sip->print();
        }

        // Pause sip
        bool pauseSip(string sipId) {

            if (sipRegistry.find(sipId) == sipRegistry.end())
                return false;

            Sip* sip = sipRegistry[sipId];
            if (sip->status == Active)
                sip->status = Paused;
            return true;
        }

        // Resume sip
        bool resumeSip(string sipId) {

            if (!sipRegistry.count(sipId))
                return false;

            Sip* sip = sipRegistry[sipId];
            if (sip->status == Paused)
                sip->status = Active;
            return true;
        }

        // Executes SIP and allocates units
        void sipExecute(int currentDay) {
            cout<<"Running SIP execution day: "<<currentDay<<endl;

            for(auto& kv: sipRegistry) {
                Sip* sip = kv.second;
                
                if (!sip->shouldExecute(currentDay)) {
                    continue;
                }

                MutualFund* fund = fundService->getMutualFund(sip->mutualFundId);
                double unitsAllocated = sip->amount / fund->currentVal;

                cout<<"Executing SIP "
                    <<sip->id
                    <<", User "
                    <<sip->userId
                    <<", Fund "
                    <<fund->name
                    <<", Amount "
                    <<sip->amount
                    <<", Units Allocated "
                    <<unitsAllocated<<endl;

                // Here the payment service is called
                // Once it responds OK/Non-OK, callback can update the SIP's run iteration status.
                // For run iteration, we can store execution results per SIP level.
            }
        }

};

int main() {
    FundService* fundService = new FundService();
    UserService* userService = new UserService();

    fundService->addMutualFund("f1", "Nifty", 100);
    fundService->addMutualFund("f2", "Sensex", 50);

    userService->addUser("u1", "Arnab");

    SipService* sipService = new SipService(fundService, userService);

    cout<<"Test getAllMutualFunds() "<<endl;
    sipService->getMutualFunds();

    cout<<"Test setupSip() "<<endl;
    string sip1 = sipService->setupSip("u1", "f1", 5000, Cadence::Weekly, 1);
    string sip2 = sipService->setupSip("u1", "f2", 2000, Cadence::Monthly, 1);

    cout<<"Test displaySip() "<<endl;
    sipService->displaySips("u1");

    cout<<"Test executeSip() "<<endl;
    sipService->sipExecute(1);

    cout<<"Test PauseSip() "<<endl;
    sipService->pauseSip(sip2);
    sipService->sipExecute(1);
    
    cout<<"Test executeSip() on different dates "<<endl;
    sipService->resumeSip(sip2);
    sipService->sipExecute(8);
    sipService->sipExecute(20);
    sipService->sipExecute(31);
}
