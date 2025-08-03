/**
6.

import java.util.*;
public class Main {
    public static int courtNumber = 0 ;
    public static void main(String[] args) {
        Game g1 = new Game(1,1,3);
        Game g2 = new Game(2,2,4); // Only Peek Here
        Game g3 = new Game(3,3,5); // Pop Here
        Game g4 = new Game(4,3,8);
        Game g5 = new Game(5,7,9);
        List<Game> finalResult = assignCourts(List.of(g1,g2,g3,g4,g5));
        System.out.println(finalResult);
        System.out.println("Total number of Courts Used " +  courtNumber);
    }

 GameId -INt
StarTime,EndTime - Int
Start is inclusive.
End is exclusive.

GameId -  [StartTime,EndTime]
GameId
...

CourtID

Implement a function that given a list of tennis court bookings with start and finish times,
returns a plan assigning each booking to a specific court,
ensuring each court is used by only one booking at a time and
using the minimum amount of courts with unlimited number of courts available.

NOTE: Same can be questioned as min number of meeting rooms required for given meetings.
Which meeting room is allocated to which meeting if you are to use min num of meeting rooms in inf availability.
 */

#include<bits/stdc++.h>
#include<iostream>
using namespace std;

class Game {
    public:
        int id;
        int startTime;
        int endTime;
        int court;

        Game(int id, int startTime, int endTime) {
            this->id = id;
            this->startTime = startTime;
            this->endTime = endTime;
            court = -1;
        }
};

class Comp {
    public:
        bool operator()(Game* g1, Game* g2) {
            if(g1->endTime > g2->endTime) {
                return true;
            } else if(g1->endTime == g2->endTime) {
                return g1->startTime > g2->startTime;
            }
            return false;
        }
};

class CourtAssigner {
    vector<Game*> gamesPlayed;
    int numCourtUsed;
    public:
        CourtAssigner() {
            numCourtUsed = 0;
        }

        vector<Game*> assignCourt(vector<Game*> games) {
            priority_queue<Game*, vector<Game*>, Comp> pq;
            for (auto game: games) {
                if (pq.empty() || (pq.top())->endTime > game->startTime) {
                    game->court = pq.size() + 1;
                    pq.push(game);
                }
                else {
                    Game* gameToBePopped = pq.top();
                    game->court = gameToBePopped->court;
                    pq.pop();
                    pq.push(game);
                }
            }
            this->gamesPlayed = games;
            numCourtUsed = pq.size();
            return this->gamesPlayed;
        }

        int getNumCourtsUsed() {
            return numCourtUsed;
        }
};

int main() {
    CourtAssigner* ca = new CourtAssigner();
    Game* g1 = new Game(1,1,3);
    Game* g2 = new Game(2,2,4); // Only Peek Here
    Game* g3 = new Game(3,3,5); // Pop Here
    Game* g4 = new Game(4,3,8);
    Game* g5 = new Game(5,7,9);
    Game* g6 = new Game(6,7,10);
    Game* g7 = new Game(7,8,10);
    Game* g8 = new Game(8,9,10);

    vector<Game*> res = ca->assignCourt({ g1, g2, g3, g4, g5, g6, g7, g8});
    for(auto game: res) {
        cout<<game->id<<" ("<<game->startTime<<", "<<game->endTime<<") : "<<game->court<<endl;
    }
    cout<<"Num court used : "<<ca->getNumCourtsUsed()<<endl;
    return 0;
}