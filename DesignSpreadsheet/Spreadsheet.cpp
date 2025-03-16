#include <bits/stdc++.h>
#include <iostream>
using namespace std;

class Spreadsheet
{
private:
    vector<vector<int> > cells;

    int getColIndex(string cell)
    {
        return cell[0] - 'A';
    }

    int getRowIndex(string cell)
    {
        int rowIndex = 0;
        for (int i = 1; i < cell.size(); i++)
        {
            rowIndex = rowIndex * 10 + (cell[i] - '0');
        }
        return rowIndex;
    }

    // check if it's a cellId or a integer value
    bool isCell(string cell)
    {
        if (cell[0] - 'A' >= 0 && cell[0] - 'A' < 26)
        {
            return true;
        }
        return false;
    }

    // tokenize a string on given del
    vector<string> tok(string s, char del)
    {
        vector<string> res;
        string temp = "";
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == del)
            {
                res.push_back(temp);
                temp = "";
                continue;
            }
            temp += s[i];
        }
        res.push_back(temp);
        return res;
    }

public:
    Spreadsheet(int rows)
    {
        cells.clear();
        cells.resize(rows + 1, vector<int>(26, 0));
    }

    void setCell(string cell, int value)
    {
        cells[getRowIndex(cell)][getColIndex(cell)] = value;
    }

    void resetCell(string cell)
    {
        cells[getRowIndex(cell)][getColIndex(cell)] = 0;
    }

    int getValue(string formula)
    {
        vector<string> operands = tok(tok(formula, '=')[1], '+');
        int val1 = isCell(operands[0])
                       ? cells[getRowIndex(operands[0])][getColIndex(operands[0])]
                       : stoi(operands[0]);
        int val2 = isCell(operands[1])
                       ? cells[getRowIndex(operands[1])][getColIndex(operands[1])]
                       : stoi(operands[1]);
        return val1 + val2;
    }
};

/**
 * Your Spreadsheet object will be instantiated and called as such:
 * Spreadsheet* obj = new Spreadsheet(rows);
 * obj->setCell(cell,value);
 * obj->resetCell(cell);
 * int param_3 = obj->getValue(formula);
 */
int main()
{
    Spreadsheet *obj = new Spreadsheet(100);
    cout<<obj->getValue("=5+7")<<endl;
    obj->setCell("A10", 10);
    obj->setCell("Z15", 25);
    cout<<obj->getValue("=A10+Z15")<<endl;
    obj->resetCell("A10");
    cout<<obj->getValue("=A10+Z15")<<endl;
}