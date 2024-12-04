#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int part1();
int part2();

int main()
{
    cout << part1();
    // cout << part2();
}

int substrCount(string str, string substr)
{
    int count = 0;
    for (int i = 0; i < str.size() - 1; i++)
    {
        int m = 0;
        int n = i;
        for (int j = 0; j < substr.size(); j++)
        {
            if (str[n] == substr[j])
                m++;
            n++;
        }
        if (m == substr.size())
            count++;
    }
    return count;
}

int helperXMAS(vector<string> content, int x, int y)
{
    string check = "";

    const int directions[8][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};

    for (auto &dir : directions)
    {
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dir[0] * i;
            int ny = y + dir[1] * i;

            if (nx >= 0 && nx < content.size() && ny >= 0 && ny < content[0].size())
                check += content[nx][ny];
        }
    }

    return substrCount(check, "XMAS");
}

int countXMAS(vector<string> content)
{
    int m = content.size();
    int n = content[0].size();

    int res = 0;

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (content[i][j] == 'X')
                res += helperXMAS(content, i, j);

    return res;
}

int part1()
{
    ifstream input("input.txt");
    string line;

    vector<string> content;

    while (getline(input, line))
        content.push_back(line);

    return countXMAS(content);
}

int helperMAS(vector<string> content, int x, int y)
{
    string check = "";

    const int directions[4][2] = {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}};

    for (auto &dir : directions)
    {
        for (int i = -1; i <= 1; i++)
        {
            int nx = x + dir[0] * i;
            int ny = y + dir[1] * i;

            if (nx >= 0 && nx < content.size() && ny >= 0 && ny < content[0].size())
                check += content[nx][ny];
        }
    }
    return substrCount(check, "MAS") >= 2;
}

int countMAS(vector<string> content)
{
    int m = content.size();
    int n = content[0].size();

    int res = 0;

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (content[i][j] == 'A')
                res += helperMAS(content, i, j);

    return res;
}

int part2()
{
    ifstream input("input.txt");
    string line;

    vector<string> content;

    while (getline(input, line))
        content.push_back(line);

    return countMAS(content);
}