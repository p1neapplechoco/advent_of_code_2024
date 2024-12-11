#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <unordered_map>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

void readFile(string filename, unordered_map<char, vector<pair<int, int>>> &antennas, int &m, int &n);

int part1();
int part2();

int main()
{
    cout << "Part 1: " << part1() << endl;
    cout << "Part 2: " << part2() << endl;
}

void readFile(string filename, unordered_map<char, vector<pair<int, int>>> &antennas, int &m, int &n)
{
    ifstream input("input.txt");
    string line;

    m = 0;
    while (getline(input, line))
    {
        for (n = 0; n < line.size(); n++)
            if (line[n] != '.')
                antennas[line[n]].push_back({m, n});
        m++;
    }
    input.close();
}

int countAntinodesPart1(unordered_map<char, vector<pair<int, int>>> antennas, int m, int n)
{
    set<pair<int, int>> antinodes;
    for (auto &antenna : antennas)
    {
        for (auto &first_a : antenna.second)
            for (auto &second_a : antenna.second)
            {
                if (first_a == second_a)
                    continue;
                int x1 = 2 * first_a.first - second_a.first;
                int y1 = 2 * first_a.second - second_a.second;

                int x2 = 2 * second_a.first - first_a.first;
                int y2 = 2 * second_a.second - first_a.second;

                if (x1 < m && x1 > -1 && y1 < n && y1 > -1)
                    antinodes.insert({x1, y1});

                if (x2 < m && x2 > -1 && y2 < n && y2 > -1)
                    antinodes.insert({x2, y2});
            }
    }
    return antinodes.size();
}

int part1()
{
    unordered_map<char, vector<pair<int, int>>> antennas;
    int m, n;

    readFile("input.txt", antennas, m, n);

    return countAntinodesPart1(antennas, m, n);
}

int countAntinodesPart2(unordered_map<char, vector<pair<int, int>>> antennas, int m, int n)
{
    set<pair<int, int>> antinodes;
    for (auto &antenna : antennas)
    {
        for (auto &first_a : antenna.second)
            for (auto &second_a : antenna.second)
            {
                if (first_a == second_a)
                    continue;

                int x1 = first_a.first;
                int y1 = first_a.second;

                int x2 = second_a.first;
                int y2 = second_a.second;

                int dx = first_a.first - second_a.first;
                int dy = first_a.second - second_a.second;

                while (x1 < m && y1 < n && x1 > -1 && y1 > -1)
                {
                    antinodes.insert({x1, y1});
                    x1 += dx;
                    y1 += dy;
                }

                while (x2 < m && y2 < n && x2 > -1 && y2 > -1)
                {
                    antinodes.insert({x2, y2});
                    x2 -= dx;
                    y2 -= dy;
                }
            }
    }
    return antinodes.size();
}

int part2()
{
    unordered_map<char, vector<pair<int, int>>> antennas;
    int m, n;

    readFile("input.txt", antennas, m, n);

    return countAntinodesPart2(antennas, m, n);
}