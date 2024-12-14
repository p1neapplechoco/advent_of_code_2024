#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const int nrow = 103;
const int ncol = 101;

ll part1();
ll part2();

int main()
{
    cout << "Part 1: " << part1() << endl;
    cout << "Part 2: " << part2() << endl;
}

void processPart1(vector<string> &grid, vector<int> &batches, int &x, int &y, int &v_x, int &v_y, int sec)
{
    while (v_x < 0)
        v_x = ncol + v_x;
    while (v_y < 0)
        v_y = nrow + v_y;

    ll new_x = (x + sec * v_x) % ncol;
    ll new_y = (y + sec * v_y) % nrow;

    grid[new_x][new_y] = '#';

    if (new_x == ncol / 2 || new_y == nrow / 2)
        return;

    if (new_x < ncol / 2 && new_y < nrow / 2)
        batches[0]++;

    else if (new_x < ncol / 2 && new_y > nrow / 2)
        batches[1]++;

    else if (new_x > ncol / 2 && new_y < nrow / 2)
        batches[2]++;

    else if (new_x > ncol / 2 && new_y > nrow / 2)
        batches[3]++;

    return;
}

ll part1()
{
    ifstream input("input.txt");
    string line;
    vector<int> batches(4, 0);
    vector<string> grid(nrow, string(ncol, ' '));

    int sec = 100;

    while (getline(input, line))
    {
        int x, y;
        int v_x, v_y;

        sscanf(line.c_str(), "p=%d,%d v=%d,%d", &x, &y, &v_x, &v_y);

        processPart1(grid, batches, x, y, v_x, v_y, sec);
    }

    // ofstream output("output.txt");
    // for (string l : grid)
    //     output << l << endl;
    // output.close();

    ll res = 1;
    for (ll batch : batches)
        res = res * batch;
    input.close();

    return res;
}

void processPart2(vector<string> &grid, int x, int y, int v_x, int v_y, int sec)
{
    while (v_x < 0)
        v_x = ncol + v_x;
    while (v_y < 0)
        v_y = nrow + v_y;

    ll new_x = (x + sec * v_x) % ncol;
    ll new_y = (y + sec * v_y) % nrow;

    grid[new_x][new_y] = '#';
}

ll part2()
{
    ifstream input;
    string line;
    vector<string> tmp(nrow, string(ncol, ' '));

    bool found = false;
    int res = 0;

    while (!found)
    {
        input.open("input.txt");
        res++;

        vector<string> grid(tmp);

        while (getline(input, line))
        {
            int x, y;
            int v_x, v_y;

            sscanf(line.c_str(), "p=%d,%d v=%d,%d", &x, &y, &v_x, &v_y);

            processPart2(grid, x, y, v_x, v_y, res);
        }

        // ofstream output("output.txt");
        // for (string &l : grid)
        //     output << l << endl;
        // output.close();

        for (string &l : grid)
            if (l.find("#################") != string::npos)
                found = true;
        input.close();
    }
    return res;
}