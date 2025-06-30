/** 
 * Part1: Imagine we are building an application that is used by many different customers. We want to avoid one customer being able to overload the system by sending too many requests, so we enforce a per-customer rate limit. The rate limit is defined as:

“Each customer can make X requests per Y seconds”

Assuming that customer ID is extracted somehow from the request, implement the following function.

// Perform rate limiting logic for provided customer ID. Return true if the
// request is allowed, and false if it is not.
boolean rateLimit(int customerId)

PART2:
one of our customers have bursty traffic, and are complaining about being rate limited. We want to better accomodate those customers, so we want to adopt a ‘credit’ based system. It will work as follows:

For each bucket of time, any capacity available below the limit is converted into credits for that customer

There is some maximum number of credits that a customer can accumulate

When a customer exceeds their normal request limit for a window, the credit count starts to decrease. When there are 0 credits, the customer is rate limited.

 */

#include<bits/stdc++.h>
#include<iostream>
#include<map>

using namespace std;

class RateLimiter {
    virtual bool rateLimit(int customerId, int timestamp) = 0;
};

class SlidingWindowRateLimiter : RateLimiter{
    map<int, queue<int> > reqLastYSecs;
    int x;
    int y;

    public:
        SlidingWindowRateLimiter(int x, int y) {
            this->x = x;
            this->y = y;
        }

        bool rateLimit(int customerId, int timestamp) {
            queue<int>& reqs = reqLastYSecs[customerId];
            // removing all older reqs than currentTimestamp - y for that customer
            while(!reqs.empty() && reqs.front() <= timestamp - y) {
                reqs.pop();
            }

            if (reqs.size() < x) {
                reqs.push(timestamp);
                return true;
            } else {
                return false;
            }
        }
};

class TokenBucket {
    public:
        int numTokens;
        int creditsAvailable;
        
        TokenBucket(int numTokens, int creditsAvailable) {
            this->numTokens = numTokens;
            this->creditsAvailable = creditsAvailable;
        }

        void refillBucket(int numTokens) {
            this->numTokens = numTokens;
        }

        void setCredit(int credits) {
            this->creditsAvailable = credits;
        }
};

// with credit system
class ModifiedTokenBucketRateLimiter : RateLimiter {
    int x;
    int y;
    int maxCredits;
    map<int, TokenBucket*> buckets;

    public:
        ModifiedTokenBucketRateLimiter(int x, int y, int maxCredits) {
            this->x = x;
            this->y = y;
            this->maxCredits = maxCredits;
        }

        bool rateLimit(int customerId, int timestamp) {
            if (buckets.find(customerId) == buckets.end()) {
                buckets[customerId] = new TokenBucket(x, 0);
            }

            TokenBucket* tb = buckets[customerId];
            if (tb->numTokens > 0) {
                tb->numTokens -= 1;
                return true;
            }
            if (tb->creditsAvailable > 0) {
                cout<<"Credits used"<<" ";
                tb->creditsAvailable -= 1;
                return true;
            }
            return false;
        }

        // run at y sec interval
        void refillBuckets() {
            for(auto kv: buckets) {
                TokenBucket* tb = kv.second;
                // pending tokens are added as credits, limited by maxCredits.
                tb->setCredit(min(this->maxCredits, tb->creditsAvailable + tb->numTokens));  
                tb->refillBucket(x);
            }
        }
};

int main() {
    // SlidingWindowRateLimiter* rl = new SlidingWindowRateLimiter(3, 5);
    // cout<<rl->rateLimit(1, 1)<<endl;
    // cout<<rl->rateLimit(1, 1)<<endl;
    // cout<<rl->rateLimit(1, 2)<<endl;
    // cout<<rl->rateLimit(1, 2)<<endl;
    // cout<<rl->rateLimit(1, 3)<<endl;
    // cout<<rl->rateLimit(1, 7)<<endl;
    // cout<<rl->rateLimit(1, 8)<<endl;
    // cout<<rl->rateLimit(1, 9)<<endl;
    // cout<<rl->rateLimit(1, 9)<<endl;
    // cout<<rl->rateLimit(2, 9)<<endl;
    

    ModifiedTokenBucketRateLimiter* rl1 = new ModifiedTokenBucketRateLimiter(2, 5, 1);
    cout<<rl1->rateLimit(1, 1)<<endl;
    cout<<rl1->rateLimit(1, 1)<<endl;
    cout<<rl1->rateLimit(1, 2)<<endl;
    cout<<rl1->rateLimit(1, 2)<<endl;
    cout<<rl1->rateLimit(1, 3)<<endl;
    cout<<rl1->rateLimit(2, 1)<<endl;    

    rl1->refillBuckets();
    cout<<rl1->rateLimit(1, 6)<<endl;
    cout<<rl1->rateLimit(2, 6)<<endl;
    cout<<rl1->rateLimit(2, 6)<<endl;
    cout<<rl1->rateLimit(2, 7)<<endl;
    cout<<rl1->rateLimit(2, 7)<<endl;

    rl1->refillBuckets();
    cout<<rl1->rateLimit(1, 11)<<endl;
    cout<<rl1->rateLimit(1, 11)<<endl;
    cout<<rl1->rateLimit(1, 12)<<endl;
    cout<<rl1->rateLimit(1, 13)<<endl;
    cout<<rl1->rateLimit(2, 12)<<endl;
    cout<<rl1->rateLimit(2, 12)<<endl;
    cout<<rl1->rateLimit(2, 12)<<endl;

    return 0;
}