/**
Design a middleware router

interface Router {
    fun addRoute(path: String, result: String) : Unit;
    fun callRoute(path: String) : String;
}

Usage:
Router.addRoute("/bar", "result")
Router.callRoute("/bar") -> output : "result"
Router.addRoute("/foo/bar", "result2")
Router.callRoute("/foo/bar") -> output: "result2"

And then follow up was that the path can have wildcard (*) in it. Need to do regex matching in that case. 
*/

#include<bits/stdc++.h>
#include<iostream>
#include<map>
using namespace std;

class Node {
    public:
        string val;
        map<string, Node*> next;

        Node() {
            this->val = "-1";
        }
};

class Router {
    Node* root;

    vector<string> tokenize(string s, char del) {
        vector<string> res;
        string temp;
        for(auto ch: s) {
            if (ch != del) {
                temp += ch;
            } else {
                res.push_back(temp);
                temp = "";
            }
        }
        res.push_back(temp);
        return res;
    }

    public:
        Router() {
            root = new Node();
        }

        bool addRoute(string path, string val) {
            Node* temp = root;
            vector<string> tokens = tokenize(path, '/');

            for (int i=1; i<tokens.size(); i++) {
                if ((temp->next).find(tokens[i]) == (temp->next).end()) {
                    temp->next[tokens[i]] = new Node();
                }
                temp = temp->next[tokens[i]];
            }
            temp->val = val;
            return true;
        }

        string callRoute(string path) {
            Node* temp = root;
            vector<string> tokens = tokenize(path, '/');

            for (int i=1; i<tokens.size(); i++) {
                if ((temp->next).find(tokens[i]) == (temp->next).end()) {
                    return "-1";
                }
                temp = temp->next[tokens[i]];
            }
            return temp->val;
        }
};

int main() {
    Router* router = new Router();
    cout<<(router->addRoute("/", "result") ? "Added" : "Not-added")<<endl;
    cout<<router->callRoute("/")<<endl;
    cout<<(router->addRoute("/bar", "result1") ? "Added" : "Not-added")<<endl;
    cout<<router->callRoute("/bar")<<endl;
    cout<<(router->addRoute("/foo/bar", "result2") ? "Added" : "Not-added")<<endl;
    cout<<router->callRoute("/foo/bar")<<endl;
    return 0;
}



