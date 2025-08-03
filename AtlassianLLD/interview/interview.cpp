#include<bits/stdc++.h>
#include<map>
#include<set>
#include<iostream>

using namespace std;

/**
Imagine you are given a stream of content ids along with an associated action to be performed on them.
Example of contents are video, pages, posts etc. There can be two actions associated with a content id:
increasePopularity → increases the popularity of the content by 1. The popularity increases when someone comments on the content or likes the content
decreasePopularity → decreases the popularity of the content by 1. The popularity decreases when a spam bot's/users comments are deleted from the content or its likes are removed from the content
content ids are positive integers
getMostPopular() : Return the list of mostPopular content ids.
 */


// unorderedMap<contentId, popularity>
// Map<popularity, set<contents> >

// increasePopularity - O(logn)
// decreasePopularity - O(logn)
// getMostPopular - O(1)


class PopularitySystem {
    unordered_map<int, int> contentMap;
    map<int, set<int> > popularityMap;

    public:

        void increasePopularity(int contentId) {
            if (contentMap.find(contentId) == contentMap.end()) {
                contentMap[contentId] = 1;
                popularityMap[1].insert(contentId);
                return;
            }
            int currPopularity = contentMap[contentId];
            popularityMap[currPopularity].erase(contentId);
            if (popularityMap[currPopularity].empty()) {
                popularityMap.erase(currPopularity);
            }
            popularityMap[currPopularity+1].insert(contentId);
            contentMap[contentId]++;
        }

        void decreasePopularity(int contentId) {            
            int currPopularity = contentMap[contentId];
            if (currPopularity <= 1) {
                contentMap.erase(contentId);
                popularityMap[currPopularity].erase(contentId);
                if (popularityMap[currPopularity].empty()) {
                    popularityMap.erase(currPopularity);
                }
                return;
            }
            popularityMap[currPopularity].erase(contentId);
            if (popularityMap[currPopularity].empty()) {
                popularityMap.erase(currPopularity);
            }
            popularityMap[currPopularity-1].insert(contentId);
            contentMap[contentId]--;
        }

        set<int> getMostPopular() {
            return (*(popularityMap.rbegin())).second;
        }
};

void project(set<int> contentIds) {
    for (auto contentId: contentIds) {
        cout<<contentId<<" ";
    }
    cout<<endl;
}

// Testing increasePopularity
void testIncreasePopularity() {
    PopularitySystem* ps = new PopularitySystem();
    ps->increasePopularity(1);
    ps->increasePopularity(2);
    ps->increasePopularity(1);
    ps->increasePopularity(1);

    project(ps->getMostPopular());
}

void testTieInPopularity() {
    PopularitySystem* ps = new PopularitySystem();
    ps->increasePopularity(1);
    ps->increasePopularity(2);
    ps->increasePopularity(1);
    ps->increasePopularity(1);
    ps->increasePopularity(2);
    ps->increasePopularity(2);

    project(ps->getMostPopular());
}

void testDecreaseInPopularity() {
    PopularitySystem* ps = new PopularitySystem();
    ps->decreasePopularity(1);
    project(ps->getMostPopular());
}

void testMixedInPopularity() {
    PopularitySystem* ps = new PopularitySystem();
    ps->increasePopularity(1);
    ps->increasePopularity(1);
    ps->increasePopularity(2);
    project(ps->getMostPopular());
    ps->decreasePopularity(1);
    project(ps->getMostPopular());
    ps->decreasePopularity(1);
    project(ps->getMostPopular());
}

int main() {
    //testIncreasePopularity();
    //testTieInPopularity();
    //testDecreaseInPopularity();
    testMixedInPopularity();
    return 0;
}