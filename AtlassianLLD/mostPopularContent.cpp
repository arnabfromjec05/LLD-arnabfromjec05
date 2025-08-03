/**
 * Create a popularity tracker of given articles.
 * 
 * interface MostPopular {
    void increasePopularity(Integer contentId);
    Integer mostPopular();
    void decreasePopularity(Integer contentId);
}
[
  popularityTracker.increasePopularity(7);
  popularityTracker.increasePopularity(7);
  popularityTracker.increasePopularity(8);
  popularityTracker.mostPopular();        // returns 7
  popularityTracker.increasePopularity(8);
  popularityTracker.increasePopularity(8);
  popularityTracker.mostPopular();        // returns 8
  popularityTracker.decreasePopularity(8);
  popularityTracker.decreasePopularity(8);
  popularityTracker.mostPopular();        // returns 7
  popularityTracker.decreasePopularity(7);
  popularityTracker.decreasePopularity(7);
  popularityTracker.decreasePopularity(8);
  popularityTracker.mostPopular();        // returns -1 since there is no content with popularity greater than 0
]

// Most popular means, contentId with heighest popularity value.

Assumptions:

In case of a tie: -> Return any contentId
Popularity of contentId can never go below zero.
 * 

 Follow-up

Return the most recent mostPopular contentId changed
Soln: used lastUpdated to break tie if many same values for mostPopular.
 */

#include<bits/stdc++.h>
#include<iostream>
#include<map>
#include<set>
using namespace std;

class Content {
    public: 
        int contentId;
        int popularity;
        long lastUpdatedTime;
    
        Content(int contentId, int popularity, long lastUpdatedTime) {
            this->contentId = contentId;
            this->popularity = popularity;
            this->lastUpdatedTime = lastUpdatedTime;
        }
};

class IMostPopular {
    public:
        virtual void increasePopularity(int contentId) = 0;
        virtual int mostPopular() = 0;
        virtual void decreasePopularity(int contentId) = 0;
};

struct Comp {
    bool operator()(Content* a, Content* b) {
        if(a->popularity > b->popularity) {
            return true;
        } else if (a->popularity == b->popularity) {
            if (a->lastUpdatedTime > b->lastUpdatedTime) {
                return true;
            } else if (a->lastUpdatedTime == b->lastUpdatedTime) {
                return a->contentId < b->contentId;
            }
        }
        return false;
    }
};

class PopularityTracker : IMostPopular{
    map<int, Content*> contentIndex;
    set<Content*, Comp> contents;
    long dateTime = 0;

    public:
        void increasePopularity(int contentId) {
            dateTime++;
            Content* content = nullptr;
            if (contentIndex.find(contentId) == contentIndex.end()) {
                content = new Content(contentId, 1, dateTime);
                contentIndex[contentId] = content;
                contents.insert(content);
            } else {
                content = contentIndex[contentId];
                contents.erase(content);
                (content->popularity)++;
                content->lastUpdatedTime = dateTime;
                contents.insert(content);
            }
        }

        void decreasePopularity(int contentId) {
            // Assuming contentId is valid and found in contentIndex
            dateTime++;
            Content* content = contentIndex[contentId];
            contents.erase(content);
            (content->popularity)--;
            content->lastUpdatedTime = dateTime;
            contents.insert(content);
        }

        int mostPopular() {
            if ((*contents.begin())->popularity > 0) {
                return (*contents.begin())->contentId;
            } else {
                return -1;
            }
        }
};

int main() {
    PopularityTracker* popularityTracker = new PopularityTracker();
    popularityTracker->increasePopularity(7);
    popularityTracker->increasePopularity(7);
    popularityTracker->increasePopularity(8);
    cout<<popularityTracker->mostPopular()<<endl;
    popularityTracker->increasePopularity(8);
    popularityTracker->increasePopularity(8);
    cout<<popularityTracker->mostPopular()<<endl;
    popularityTracker->decreasePopularity(8);
    popularityTracker->decreasePopularity(8);
    cout<<popularityTracker->mostPopular()<<endl;
    popularityTracker->decreasePopularity(7);
    popularityTracker->decreasePopularity(7);
    popularityTracker->decreasePopularity(8);
    cout<<popularityTracker->mostPopular()<<endl;
    popularityTracker->increasePopularity(6);
    popularityTracker->increasePopularity(6);
    cout<<popularityTracker->mostPopular()<<endl;
    popularityTracker->decreasePopularity(6);
    popularityTracker->increasePopularity(8);
    popularityTracker->increasePopularity(6);
    popularityTracker->increasePopularity(8);
    cout<<popularityTracker->mostPopular()<<endl;


    return 0;
}
