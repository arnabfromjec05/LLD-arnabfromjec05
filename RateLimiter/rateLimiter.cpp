// Allow only N requests per user per minute

#include<iostream>
#include<queue>
#include<map>
#include<mutex>
#include<thread>
using namespace std;

mutex atomicOutput;

class RateLimiter {
    int n;
    int timeInterval;   // 60 sec default
    map<string, queue<int> > userRequests;
    mutex mtx;

    public:
        RateLimiter(int n, int timeInterval) {
            this->n = n;
            this->timeInterval = timeInterval;
        }

        bool allow(string userId, int timestamp) {
            lock_guard<mutex> user(mtx); // locking for all users

            queue<int>& requests = userRequests[userId];            
            while(!requests.empty() &&
                timestamp - requests.front() > timeInterval) {
                    requests.pop();
                }
            
            if (requests.size() >= n) {
                return false;
            }
            requests.push(timestamp);
            return true;
        }
};

void printFunc(RateLimiter* rl, string userId, int timestamp) {
    bool res = rl->allow(userId, timestamp);
    lock_guard<mutex> lock(atomicOutput);
    cout<<"Thread"<<this_thread::get_id()<<" userId: "<<userId<<", ts: "<<timestamp<<" = "<<res<<endl;
}

int main() {

    RateLimiter* rl = new RateLimiter(5, 60);
    vector<thread> threads;

    for(int i=0; i<10; i++) {
        threads.emplace_back(printFunc, rl, "1", 5);
    }

    for(auto& t: threads) {
        t.join();
    }

    // thread t1(printFunc, rl, "1", 5);
    // thread t2(printFunc, rl, "1", 5);
    // thread t3(printFunc, rl, "1", 5);
    // thread t4(printFunc, rl, "1", 5);
    // thread t5(printFunc, rl, "1", 5);
    // thread t6(printFunc, rl, "1", 5);

    // t1.join();
    // t2.join();
    // t3.join();
    // t4.join();
    // t5.join();
    // t6.join();


    // cout<<rl->allow("2", 5);
    // cout<<rl->allow("2", 5);

    // cout<<rl->allow("1", 10);
    // cout<<rl->allow("1", 50);
    // cout<<rl->allow("1", 55);
    // cout<<rl->allow("1", 56);
    // cout<<rl->allow("1", 57);
    // cout<<rl->allow("1", 58);
    // cout<<rl->allow("1", 59);

    // cout<<rl->allow("1", 120);
    // cout<<rl->allow("1", 125);
    
    // cout<<rl->allow("2", 5);
    // cout<<rl->allow("2", 5);
    // cout<<rl->allow("2", 5);
    // cout<<rl->allow("2", 7);
    // cout<<rl->allow("2", 66);


    return 0;
}