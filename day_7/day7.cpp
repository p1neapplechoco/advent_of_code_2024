#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

typedef ll ll;
typedef unsigned long long ull;

void readFile(string filename, vector<ll> &nums, ll &target);

ll part1();
ll part2();

int main()
{
    cout << "Part 1: " << part1() << endl;
    cout << "Part 2: " << part2() << endl;
}

bool sumOrProduct(vector<ll> &nums, ll target, ll cur, int idx)
{
    if (idx >= nums.size())
        return cur == target;

    return sumOrProduct(nums, target, cur + nums[idx], idx + 1) || sumOrProduct(nums, target, cur * nums[idx], idx + 1);
}

ll part1()
{
    ifstream input("input.txt");
    string line;

    ll res = 0;

    while (getline(input, line))
    {
        vector<ll> nums;
        ll target;

        int idx = line.find(':');
        target = stoll(line.substr(0, idx += 2));
        string tmp = "";
        while (idx < line.length())
        {
            if (line[idx] == ' ')
            {
                nums.push_back(stoll(tmp));
                tmp.clear();
                idx++;
            }
            else
            {
                tmp += line[idx];
                idx++;
            }
        }

        nums.push_back(stoll(tmp));
        tmp.clear();

        if (sumOrProduct(nums, target, 0, 0))
            res += target;
    }
    return res;
}

bool concatenation(vector<ll> &nums, ll target, ll cur, int idx)
{
    if (idx >= nums.size())
        return cur == target;

    return concatenation(nums, target, cur + nums[idx], idx + 1) ||
           concatenation(nums, target, cur * nums[idx], idx + 1) ||
           concatenation(nums, target, stoll(to_string(cur) + to_string(nums[idx])), idx + 1);
}

ll part2()
{
    ifstream input("input.txt");
    string line;

    ll res = 0;

    while (getline(input, line))
    {
        vector<ll> nums;
        ll target;

        int idx = line.find(':');
        target = stoll(line.substr(0, idx += 2));
        string tmp = "";
        while (idx < line.length())
        {
            if (line[idx] == ' ')
            {
                nums.push_back(stoll(tmp));
                tmp.clear();
                idx++;
            }
            else
            {
                tmp += line[idx];
                idx++;
            }
        }

        nums.push_back(stoll(tmp));
        tmp.clear();

        if (concatenation(nums, target, 0, 0))
            res += target;
    }
    return res;
}