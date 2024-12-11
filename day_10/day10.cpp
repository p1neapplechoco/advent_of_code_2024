#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

ull part1();
ull part2();

int main()
{
    cout << "Part 1: " << part1() << endl;
    cout << "Part 2: " << part2() << endl;
}

ull dfsPart1(vector<string> grid, int x, int y, int idx, map<pair<int, int>, int> &visited)
{
    if (x < 0 || y < 0 || x >= grid.size() || y >= grid[0].size())
        return 0;

    if (grid[x][y] != idx)
        return 0;

    if (idx == '9')
    {
        if (!visited[{x, y}])
        {
            visited[{x, y}] = 1;
            return 1;
        }
        return 0;
    }

    return dfsPart1(grid, x, y + 1, idx + 1, visited) +
           dfsPart1(grid, x, y - 1, idx + 1, visited) +
           dfsPart1(grid, x + 1, y, idx + 1, visited) +
           dfsPart1(grid, x - 1, y, idx + 1, visited);
}

ull part1()
{
    set<pair<int, int>> starts;
    vector<string> grid;

    ifstream input("input.txt");

    string line;
    int r = 0;
    while (getline(input, line))
    {
        for (int i = 0; i < line.size(); i++)
            if (line[i] == '0')
                starts.insert({r, i});

        grid.push_back(line);
        r++;
    }

    ull res = 0;

    for (auto &e : starts)
    {
        map<pair<int, int>, int> visited;
        int x = e.first;
        int y = e.second;

        res += dfsPart1(grid, x, y, '0', visited);
    }

    return res;
}

ull dfsPart2(vector<string> grid, int x, int y, int idx, map<pair<int, int>, int> &visited)
{
    if (x < 0 || y < 0 || x >= grid.size() || y >= grid[0].size())
        return 0;

    if (grid[x][y] != idx)
        return 0;

    if (idx == '9')
        return 1;

    return dfsPart2(grid, x, y + 1, idx + 1, visited) +
           dfsPart2(grid, x, y - 1, idx + 1, visited) +
           dfsPart2(grid, x + 1, y, idx + 1, visited) +
           dfsPart2(grid, x - 1, y, idx + 1, visited);
}

ull part2()
{
    set<pair<int, int>> starts;
    vector<string> grid;

    ifstream input("input.txt");

    string line;
    int r = 0;
    while (getline(input, line))
    {
        for (int i = 0; i < line.size(); i++)
            if (line[i] == '0')
                starts.insert({r, i});

        grid.push_back(line);
        r++;
    }

    ull res = 0;

    for (auto &e : starts)
    {
        map<pair<int, int>, int> visited;
        int x = e.first;
        int y = e.second;

        res += dfsPart2(grid, x, y, '0', visited);
    }

    return res;
}