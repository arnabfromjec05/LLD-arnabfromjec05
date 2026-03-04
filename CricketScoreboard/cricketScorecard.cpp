#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;

enum Run {
    ZERO,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    WD,
    NB,
    WK
};

class Player {
    public:
        string name;
        int score;
        int num4s;
        int num6s;
        int ballsFaced;

        Player(string name) {
            this->name = name;
            score = 0;
            num4s = 0;
            num6s = 0;
            ballsFaced = 0;
        }

        void printStats(bool isPlaying) {
            cout<<name<<(isPlaying ? "*" : "")<<": "
                <<score<<", "
                <<num4s<<", "
                <<num6s<<", "
                <<ballsFaced<<endl;
        }
};

class Team {
    private:
        int strike = 0;
        int nonStrike = 1;

        void swap(int& strike, int& nonStrike) {
            int temp = strike;
            strike = nonStrike;
            nonStrike = temp;
        }

    public:
        int teamId;
        vector<Player*> players;
        int totalScore;
        int numWickets;
        double oversPlayed;

        Team(int teamId) {
            this->teamId = teamId;
            players = {};
            totalScore = 0;
            numWickets = 0;
            oversPlayed = 0;
        }

        void addPlayer(string name) {
            players.push_back(
                new Player(name)
            );
        }

        bool isAllOut() {
            return numWickets >= players.size()-1;
        }

        void processRun(Run run) {
            switch (run)
            {
                case Run::ZERO:
                    players[strike]->ballsFaced += 1;
                    break;
                case Run::ONE:
                    players[strike]->ballsFaced += 1;
                    players[strike]->score += 1;
                    swap(strike, nonStrike);
                    totalScore += 1;
                    break;
                case Run::TWO:
                    players[strike]->ballsFaced += 1;
                    players[strike]->score += 2;
                    totalScore += 2;
                    break;
                case Run::THREE:
                    players[strike]->ballsFaced += 1;
                    players[strike]->score += 3;
                    swap(strike, nonStrike);
                    totalScore += 3;
                    break;
                case Run::FOUR:
                    players[strike]->ballsFaced += 1;
                    players[strike]->score += 4;
                    players[strike]->num4s += 1;
                    totalScore += 4;
                    break;
                case Run::SIX:
                    players[strike]->ballsFaced += 1;
                    players[strike]->score += 6;
                    players[strike]->num6s += 1;
                    totalScore += 6;
                    break;
                case Run::WD:
                case Run::NB:
                    totalScore += 1;
                    break;
                case Run::WK:
                    players[strike]->ballsFaced += 1;
                    strike = max(strike, nonStrike) + 1;
                    numWickets += 1;
                    break;
                default:
                    break;
            }
        }

        void processOver(int numBallsThrown) {
            if (numBallsThrown == 6) {
                oversPlayed += 1;
                swap(strike, nonStrike);
            } else {
                oversPlayed += ((double)numBallsThrown)/10;
            }
        }

        void printScoreCard() {
            cout<<"Scorecard for Team "<<teamId<<":"<<endl;
            cout<<"Player Name: Score, 4s, 6s, Balls"<<endl;
            for (int i=0; i<players.size(); i++) {
                players[i]->printStats(i==strike || i==nonStrike);
            }
            cout<<"Total: "<<totalScore<<"/"<<numWickets<<endl;
            cout<<"Overs: "<<oversPlayed<<endl; 
        }
};

class Match {

    map<string, Run> strToRun = {
        { "0", Run::ZERO },
        { "1", Run::ONE },
        { "2", Run::TWO },
        { "3", Run::THREE },
        { "4", Run::FOUR },
        { "5", Run::FIVE },
        { "6", Run::SIX },
        { "W", Run::WK },
        { "Wd", Run::WD },
        { "Nb", Run::NB },
    };

    public:
        int numPlayersEachTeam;
        int numOvers;
        Team* team1;
        Team* team2;

        Match() {
            cout<<"No. of players each team: ";
            cin>>numPlayersEachTeam;
            cout<<"Num of overs: ";
            cin>>numOvers;

            team1 = new Team(1);
            cout<<"Batting order for team1: ";
            getBattingOrder(team1);
            getRuns(team1);

            team2 = new Team(2);
            cout<<"Batting order for team2: ";
            getBattingOrder(team2);
            getRuns(team2);

            announceWinner();
        }

        void getBattingOrder(Team* team) {
            string playerName;
            for (int i=0; i<numPlayersEachTeam; i++) {
                cin>>playerName;
                team->addPlayer(playerName);
            }
        }

        void getRuns(Team* team) {
            for (int i=0; i<numOvers; i++) {
                cout<<"Over"<<i+1<<":"<<endl;
                int numBallsThrown = 0;
                while(!team->isAllOut() && numBallsThrown < 6) {
                    string run;
                    cin>>run;
                    if (run == "Wd" || run == "Nb") {
                        team->processRun(strToRun[run]);
                        continue;
                    }
                    team->processRun(strToRun[run]);
                    numBallsThrown++;
                }
                team->processOver(numBallsThrown);
                team->printScoreCard();
            }
        }

        void announceWinner() {
            int winnerTeamId = team1->totalScore > team2->totalScore
                ? team1->teamId
                : team2->teamId;
            cout<<"Result: Team "<<winnerTeamId<<" won by "
                <<abs(team1->totalScore - team2->totalScore)<<" runs"<<endl;
        }
};

int main() {
    Match* match = new Match();
    return 0;
}