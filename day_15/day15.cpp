#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>

int nrow = 0;
int ncol = 0;

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

void doMovePart1(vector<string> &grid, int &x, int &y, int dx, int dy)
{
    if (grid[y + dy][x + dx] == '#')
        return;
    int i = 1;
    while (grid[y + i * dy][x + i * dx] == 'O')
    {
        if (grid[y + (i + 1) * dy][x + (i + 1) * dx] == '#')
            return;
        if (grid[y + (i + 1) * dy][x + (i + 1) * dx] == '.')
        {
            while (i > 0)
            {
                swap(grid[y + i * dy][x + i * dx], grid[y + (i + 1) * dy][x + (i + 1) * dx]);
                i--;
            }
            break;
        }
        i++;
    }

    grid[y + dy][x + dx] = '@';
    grid[y][x] = '.';
    x += dx;
    y += dy;
}

void processPart1(vector<string> &grid, int &x, int &y, string moves)
{
    for (char move : moves)
        if (move == '<')
            doMovePart1(grid, x, y, -1, 0);
        else if (move == '>')
            doMovePart1(grid, x, y, 1, 0);
        else if (move == '^')
            doMovePart1(grid, x, y, 0, -1);
        else if (move == 'v')
            doMovePart1(grid, x, y, 0, 1);
}

ll part1()
{
    ifstream input("input.txt");
    string line;
    ll res = 0;

    vector<string> grid;
    int x = 0;
    int y = 0;

    while (getline(input, line))
    {
        if (line.empty())
            break;

        if (line.find("@") != string::npos)
        {
            x = line.find("@");
            y = grid.size();
        }

        grid.push_back(line);
    }

    while (getline(input, line))
        processPart1(grid, x, y, line);

    for (int i = 0; i < grid.size(); i++)
        for (int j = 0; j < grid[i].size(); j++)
            if (grid[i][j] == 'O')
                res += 100 * i + j;

    return res;
}

void dfsBoxes(vector<string> &grid, int x, int y, int dx, int dy, set<pair<int, int>> &adj)
{
    if (grid[y][x] == '#' || grid[y][x] == '.')
        return;

    if (grid[y][x] == ']')
    {
        adj.insert({y, x - 1});
        dfsBoxes(grid, x - 1 + dx, y + dy, dx, dy, adj);
    }

    else if (grid[y][x] == '[')
    {
        adj.insert({y, x});
        dfsBoxes(grid, x + 1 + dx, y + dy, dx, dy, adj);
    }

    dfsBoxes(grid, x + dx, y + dy, dx, dy, adj);
}

bool moveMultipleBoxes(vector<string> &grid, set<pair<int, int>> &adj, int dx, int dy, int i)
{
    vector<pair<int, int>> boxes(adj.begin(), adj.end());

    for (auto &box : boxes)
    {
        int by = box.first;
        int bx = box.second;

        if (grid[by + dy][bx + dx] == '#' || grid[by + dy][bx + dx + 1] == '#')
            return false;
    }

    for (int j = (dy < 0) ? 0 : boxes.size() - 1; (dy < 0) ? j < boxes.size() : j >= 0; (dy < 0) ? j++ : j--)
    {
        int by = boxes[j].first;
        int bx = boxes[j].second;

        if (grid[by + dy][bx + dx] == '#' || grid[by + dy][bx + dx] == '#')
            continue;

        grid[by + dy][bx + dx] = '[';
        grid[by][bx] = '.';

        grid[by + dy][bx + dx + 1] = ']';
        grid[by][bx + 1] = '.';
    }
    return true;
}

void doMovePart2(vector<string> &grid, int &x, int &y, int dx, int dy)
{
    if (grid[y + dy][x + dx] == '#')
        return;

    if (dy == 0)
    {
        int i = 1;
        while (grid[y][x + i * dx] != '.')
        {
            if (grid[y][x + (i + 2) * dx] == '#')
                return;
            if (grid[y][x + (i + 2) * dx] == '.')
            {
                i++;
                while (i > 0)
                {
                    swap(grid[y][x + i * dx], grid[y][x + (i + 1) * dx]);
                    i--;
                }
                break;
            }
            i += 2;
        }
    }
    else
    {
        set<pair<int, int>> adj;
        dfsBoxes(grid, x, y, dx, dy, adj);

        int i = 1;
        while (grid[y + i * dy][x] != '.')
        {
            if (grid[y + (i + 1) * dy][x] == '#')
                return;
            if (grid[y + (i + 1) * dy][x] == '.')
            {
                if (!moveMultipleBoxes(grid, adj, dx, dy, i))
                    return;
                break;
            }
            i++;
        }
    }

    grid[y + dy][x + dx] = '@';
    grid[y][x] = '.';
    x += dx;
    y += dy;
}

void processPart2(vector<string> &grid, int &x, int &y, string moves)
{
    for (char move : moves)
        if (move == '<')
            doMovePart2(grid, x, y, -1, 0);
        else if (move == '>')
            doMovePart2(grid, x, y, 1, 0);
        else if (move == '^')
            doMovePart2(grid, x, y, 0, -1);
        else if (move == 'v')
            doMovePart2(grid, x, y, 0, 1);
}

ll part2()
{
    ifstream input("input.txt");
    string line;
    ll res = 0;

    vector<string> grid;

    int x = 0;
    int y = 0;

    while (getline(input, line))
    {
        if (line.empty())
            break;

        string tmp = "";
        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] == '.')
                tmp += "..";
            else if (line[i] == '#')
                tmp += "##";
            else if (line[i] == 'O')
                tmp += "[]";
            else if (line[i] == '@')
                tmp += "@.";
        }

        if (tmp.find("@") != string::npos)
        {
            x = tmp.find("@");
            y = grid.size();
        }

        grid.push_back(tmp);
    }

    while (getline(input, line))
        processPart2(grid, x, y, line);

    for (int i = 0; i < grid.size(); i++)
        for (int j = 0; j < grid[i].size(); j++)
            if (grid[i][j] == '[')
                res += 100 * i + j;

    return res;
}