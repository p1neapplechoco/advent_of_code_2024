#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>
#include <map>

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

ull blinkDP(ull n, map<pair<ull, int>, ull> &dp, int times)
{
    if (times == 0)
        return 1;

    if (dp.find({n, times}) != dp.end())
        return dp[{n, times}];

    if (n == 0)
        dp[{n, times}] = blinkDP(1, dp, times - 1);
    else if (int(log10(n) + 1) % 2 == 0)
    {
        string tmp = to_string(n);
        int ss = tmp.size();

        dp[{n, times}] = blinkDP(stoull(tmp.substr(0, ss / 2)), dp, times - 1) + blinkDP(stoull(tmp.substr(ss / 2)), dp, times - 1);
    }
    else
        dp[{n, times}] = blinkDP(n * 2024, dp, times - 1);

    return dp[{n, times}];
}

ull part1()
{
    ifstream input("input.txt");
    string line;
    ull res = 0;

    vector<ull> stones;

    while (getline(input, line))
    {
        stringstream ss(line);
        long long stone;

        while (ss >> stone)
            stones.push_back(stone);
    }

    map<pair<ull, int>, ull> dp;

    for (int stone : stones)
        res += blinkDP(stone, dp, 25);

    return res;
}

ull part2()
{
    ifstream input("input.txt");
    string line;
    ull res = 0;

    vector<ull> stones;

    while (getline(input, line))
    {
        stringstream ss(line);
        long long stone;

        while (ss >> stone)
            stones.push_back(stone);
    }

    map<pair<ull, int>, ull> dp;

    for (int stone : stones)
        res += blinkDP(stone, dp, 75);

    return res;
}