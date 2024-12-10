#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

unsigned long long part1();
unsigned long long part2();

int main()
{
    cout << "Part 1:" << part1() << endl;
    cout << "Part 2:" << part2() << endl;
}

unsigned long long helperPart1(string line)
{
    vector<int> tmp;

    for (int i = 0; i < line.size(); i++)
        if (i % 2)
            while (line[i]-- - '0')
                tmp.push_back(-1);
        else
            while (line[i]-- - '0')
                tmp.push_back(i / 2);

    int l = 0;
    int r = tmp.size() - 1;

    while (l < r)
    {
        while (tmp[l] != -1)
            l++;

        while (tmp[r] == -1)
            r--;
        if (l >= r)
            break;
        swap(tmp[l], tmp[r]);
        continue;
    }

    ofstream output("output.txt");
    for (auto e : tmp)
        output << e << ",";
    output.close();

    unsigned long long res = 0;

    for (int i = 0; tmp[i] != -1; i++)
        res += (i * tmp[i]);

    return res;
}

unsigned long long part1()
{
    ifstream input("input.txt");
    string line;

    getline(input, line);

    input.close();

    return helperPart1(line);
}

unsigned long long helperPart2(string line)
{
    vector<int> tmp;

    for (int i = 0; i < line.size(); i++)
        if (i % 2)
            while (line[i]-- - '0')
                tmp.push_back(-1);
        else
            while (line[i]-- - '0')
                tmp.push_back(i / 2);

    unsigned long long res = 0;

    int r_r = tmp.size() - 1;
    int r_l = r_r;

    int idx = tmp[tmp.size() - 1];

    while (r_l > -1)
    {
        while (tmp[r_r] == -1)
            r_r--;

        r_l = r_r;

        while (tmp[r_l - 1] == tmp[r_r])
            r_l--;

        int l_l = 0;

        while (tmp[l_l] != -1)
            l_l++;

        int l_r = l_l;
        while (l_r - l_l < r_r - r_l && l_r < r_l)
        {
            while (tmp[l_l] != -1)
                l_l++;

            l_r = l_l;

            while (tmp[l_r + 1] == -1)
                l_r++;

            if (l_r - l_l < r_r - r_l)
            {
                l_l = l_r + 1;
                continue;
            }
        }

        if (l_r > r_l)
        {
            r_r = r_l - 1;
            continue;
        }

        for (; r_r > r_l - 1; r_r--)
            swap(tmp[l_l++], tmp[r_r]);

        r_r = r_l - 1;
        idx--;
    }

    for (int i = 0; i < tmp.size(); i++)
        if (tmp[i] != -1)
            res += (i * tmp[i]);

    return res;
}

unsigned long long part2()
{
    ifstream input("input.txt");
    string line;

    getline(input, line);

    input.close();

    return helperPart2(line);
}