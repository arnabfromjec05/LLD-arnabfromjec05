#include<iostream>
#include<queue>
#include<mutex>
#include<condition_variable>
#include<thread>
using namespace std;

template <typename T>
class BlockingQueue {
    queue<T> queue;
    int capacity;
    mutex mtx;
    condition_variable notFull;
    condition_variable notEmpty;

    public:
        BlockingQueue(int capacity) {
            this->capacity = capacity;
        }

        bool push(T ele) {
            unique_lock<mutex> lock(mtx);

            // wait until queue has space
            notFull.wait(lock, [this]() { return queue.size() < capacity; });

            // do operation
            queue.push(ele);

            lock.unlock();
            notEmpty.notify_one();
            return true;
        }

        T pop() {
            unique_lock<mutex> lock(mtx);
            // wait until queue has atleast one element
            notEmpty.wait(lock, [this]() { return !queue.empty(); });

            // do operation
            T ele = queue.front();
            queue.pop();
            
            lock.unlock();
            notFull.notify_one();
            return ele;
        }
};

int main() {

    BlockingQueue<int> q(5);
    mutex printingMtx;

    thread th1([&q, &printingMtx]() {
        for (int i=0; i<10; i++) {
            bool res = q.push(i);
            if (res) {
                lock_guard<mutex> lock(printingMtx);
                cout<<"Published element : "<<i<<endl;
            } else {
                lock_guard<mutex> lock(printingMtx);
                cout<<"Coudn't publish element";
            }
        }
    });

    thread th2([&q, &printingMtx]() {
        for (int i=0; i<10; i++) {
            int ele = q.pop();
            lock_guard<mutex> lock(printingMtx);
            cout<<"Consumed element : "<<ele<<endl;
        }
    });

    th1.join();
    th2.join();

    return 0;
}

/**
 * Note:
 * in c++, wait() always requires a unique_lock(). lock it before waiting. unlock it before notifying.
 * wait() does is:
 *  thread releases lock
 *  thread sleeps
 *  thread wakes up
 *  thread tries acquiring lock
 */