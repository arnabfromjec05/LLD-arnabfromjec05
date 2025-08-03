#include<bits/stdc++.h>
#include<map>
#include<set>
#include<iostream>
#include <list>

using namespace std;

/**
 * interface SnakeGame {
    moveSnake(snakeDirection); // O(sizeof(snake))
    isGameOver(); // When snake hits itself // O(sizeof(snake))
}

direction = UP, DOWN, LEFT, RIGHT
snake size = 3
every 5 move snake grow by 1

i/p:
"RIGHT","RIGHT","RIGHT","UP","LEFT","LEFT","LEFT","LEFT","DOWN","RIGHT","UP"
 * 
 * 
 */

enum Direction {
    UP,
    DOWN,
    RIGHT,
    LEFT
};

class Snake {
    list<pair<int, int> > snake;
    public:
        Snake() {
            this->snake = {{0,0}, {1,0}, {2,0}};
        }

        list<pair<int, int> > getSnake() {
            return snake;
        }

        void moveToDirection(Direction dir, int boardX, int boardY) {
            pair<int, int> head;
            switch(dir) {
                case Direction::UP:
                    head = (this->snake).back();
                    (this->snake).pop_front();
                    (this->snake).push_back({head.first, (head.second + 1) % boardY});
                    break;
                case Direction::DOWN:
                    head = (this->snake).back();
                    (this->snake).pop_front();
                    (this->snake).push_back({head.first, ((head.second - 1) + boardY) % boardY});       // [,0] -> [,-1+5 = 4]
                    break;
                case Direction::LEFT:
                    head = (this->snake).back();
                    (this->snake).pop_front();
                    (this->snake).push_back({((head.first - 1) + boardX) % boardX, head.second});
                    break;
                case Direction::RIGHT:
                    head = (this->snake).back();
                    (this->snake).pop_front();
                    (this->snake).push_back({(head.first + 1) % boardX, head.second});
                    break;
            }
        }

        void printSnake() {
            for(auto pair: snake) {
                cout<<"("<<pair.first<<", "<<pair.second<<") ";
            }
            cout<<endl;
        }
};

class SnakeGame {
    Snake* snake;
    int boardX, boardY;
    public:
        SnakeGame(int boardX, int boardY) {
            this->boardX = boardX;
            this->boardY = boardY;
            snake = new Snake();
        }

        void moveSnake(Direction dir) {
            snake->moveToDirection(
                dir, this->boardX, this->boardY);
        }   
        
        bool isGameOver() {
            bool isSnakeBiting = false;
            set<pair<int, int> > seenPair;
            for (auto pair: snake->getSnake()) {
                if (seenPair.find(pair) != seenPair.end()) {
                    return true;
                }
                seenPair.insert(pair);
            }
            return false;
        }

        void printSnakeCoordinates() {
            snake->printSnake();
        }
};

int main() {

    SnakeGame* sg = new SnakeGame(10, 10);
    sg->moveSnake(Direction::RIGHT);
    sg->moveSnake(Direction::RIGHT);
    sg->moveSnake(Direction::RIGHT);

    sg->moveSnake(Direction::UP);
    sg->moveSnake(Direction::LEFT);
    sg->moveSnake(Direction::LEFT);
    sg->moveSnake(Direction::DOWN);

    sg->printSnakeCoordinates();
    cout<<sg->isGameOver()<<endl;


    return 0;
}