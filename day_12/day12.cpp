#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

ll part1();
ll part2();

int main()
{
    cout << "Part 1: " << part1() << endl;
    cout << "Part 2: " << part2() << endl;
}

bool isValid(vector<string> &garden, int i, int j)
{
    return i >= 0 && i < garden.size() && j >= 0 && j < garden[i].size();
}

void countAreaAndPerimeter(vector<string> &garden, int i, int j, char type, set<pair<int, int>> &visited, int &area, int &perimeter)
{
    if (!isValid(garden, i, j) || garden[i][j] != type || visited.count({i, j}))
        return;

    visited.insert({i, j});
    int extra = 4;

    if (i < garden.size() - 1)
        if (garden[i + 1][j] == type)
            extra--;
    if (i > 0)
        if (garden[i - 1][j] == type)
            extra--;
    if (j < garden[i].size() - 1)
        if (garden[i][j + 1] == type)
            extra--;
    if (j > 0)
        if (garden[i][j - 1] == type)
            extra--;

    perimeter += extra;
    area++;

    countAreaAndPerimeter(garden, i + 1, j, type, visited, area, perimeter);
    countAreaAndPerimeter(garden, i - 1, j, type, visited, area, perimeter);
    countAreaAndPerimeter(garden, i, j + 1, type, visited, area, perimeter);
    countAreaAndPerimeter(garden, i, j - 1, type, visited, area, perimeter);
}

ll part1()
{
    ifstream input("input.txt");
    string line;
    ll res = 0;

    vector<string> garden;

    while (getline(input, line))
    {
        garden.push_back(line);
    }

    set<pair<int, int>> visited;

    for (int i = 0; i < garden.size(); i++)
    {
        for (int j = 0; j < garden[i].size(); j++)
        {
            int area = 0;
            int perimeter = 0;
            countAreaAndPerimeter(garden, i, j, garden[i][j], visited, area, perimeter);

            res += area * perimeter;
        }
    }

    return res;
}

void dfs(vector<string> &garden, int i, int j, char type, set<pair<int, int>> &visited, set<pair<int, int>> &land)
{
    if (isValid(garden, i, j) || garden[i][j] != type || visited.count({i, j}))
        return;

    visited.insert({i, j});
    land.insert({i, j});

    dfs(garden, i + 1, j, type, visited, land);
    dfs(garden, i - 1, j, type, visited, land);
    dfs(garden, i, j + 1, type, visited, land);
    dfs(garden, i, j - 1, type, visited, land);
}

int getSides(vector<string> &garden, set<pair<int, int>> land, char type)
{
    int res = 0;

    for (auto &pos : land)
    {
        int i = pos.first;
        int j = pos.second;

        if (!isValid(garden, i - 1, j) || (isValid(garden, i - 1, j) && garden[i - 1][j] != type))
        {
            res++;
            if (land.find({i, j - 1}) != land.end() && (!isValid(garden, i - 1, j - 1) || garden[i - 1][j - 1] != type))
                res--;
        }

        if (!isValid(garden, i + 1, j) || (isValid(garden, i + 1, j) && garden[i + 1][j] != type))
        {
            res++;
            if (land.find({i, j - 1}) != land.end() && (!isValid(garden, i + 1, j - 1) || garden[i + 1][j - 1] != type))
                res--;
        }

        if (!isValid(garden, i, j - 1) || (isValid(garden, i, j - 1) && garden[i][j - 1] != type))
        {
            res++;
            if (land.find({i - 1, j}) != land.end() && (!isValid(garden, i - 1, j - 1) || garden[i - 1][j - 1] != type))
                res--;
        }

        if (!isValid(garden, i, j + 1) || (isValid(garden, i, j + 1) && garden[i][j + 1] != type))
        {
            res++;
            if (land.find({i - 1, j}) != land.end() && (!isValid(garden, i - 1, j + 1) || garden[i - 1][j + 1] != type))
                res--;
        }
    }

    return res;
}

ll part2()
{
    ifstream input("input.txt");
    string line;
    ll res = 0;

    vector<string> garden;

    while (getline(input, line))
    {
        garden.push_back(line);
    }

    set<pair<int, int>> visited;

    for (int i = 0; i < garden.size(); i++)
    {
        for (int j = 0; j < garden[i].size(); j++)
        {
            set<pair<int, int>> land;
            dfs(garden, i, j, garden[i][j], visited, land);

            res += land.size() * getSides(garden, land, garden[i][j]);
        }
    }

    return res;
}