#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void readFile(string filename, vector<long long> &nums, long long &target);

long long part1();
long long part2();

int main()
{
    cout << part1();
    cout << part2();
}

bool sumOrProduct(vector<long long> &nums, long long target, long long cur, int idx)
{
    if (idx >= nums.size())
        return cur == target;

    return sumOrProduct(nums, target, cur + nums[idx], idx + 1) || sumOrProduct(nums, target, cur * nums[idx], idx + 1);
}

long long part1()
{
    ifstream input("input.txt");
    string line;

    long long res = 0;

    while (getline(input, line))
    {
        vector<long long> nums;
        long long target;

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

bool concatenation(vector<long long> &nums, long long target, long long cur, int idx)
{
    if (idx >= nums.size())
        return cur == target;

    return concatenation(nums, target, cur + nums[idx], idx + 1) ||
           concatenation(nums, target, cur * nums[idx], idx + 1) ||
           concatenation(nums, target, stoll(to_string(cur) + to_string(nums[idx])), idx + 1);
}

long long part2()
{
    ifstream input("input.txt");
    string line;

    long long res = 0;

    while (getline(input, line))
    {
        vector<long long> nums;
        long long target;

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