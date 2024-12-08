#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

int part1();
int part2();

bool isSafePart1(vector<int> &);
bool isSafePart2(vector<int> &);

int main()
{
    cout << "Part 1: " << part1() << endl;
    cout << "Part 2: " << part2() << endl;
}

int part1()
{
    int res = 0;
    ifstream input("input.txt");
    string line;

    while (getline(input, line))
    {
        vector<int> nums;

        for (int i = 0; i < line.size(); i++)
        {
            string tmp{};
            while (line[i] != ' ')
                tmp += line[i++];
            nums.push_back(stoi(tmp));
        }

        if (isSafePart1(nums))
            res++;
    }

    return res;
}

int part2()
{
    int res = 0;
    ifstream input("input.txt");
    string line;

    while (getline(input, line))
    {
        vector<int> nums;

        for (int i = 0; i < line.size(); i++)
        {
            string tmp{};
            while (line[i] != ' ')
                tmp += line[i++];
            nums.push_back(stoi(tmp));
        }

        if (isSafePart2(nums))
            res++;
    }

    return res;
}

bool isSafePart1(vector<int> &nums)
{
    if (nums[1] == nums[0])
        return false;

    bool isDescending = (nums[1] - nums[0] > 0);

    for (int i = 0; i < nums.size() - 1; i++)
    {
        int d = nums[i + 1] - nums[i];
        bool check = d > 0;
        if (abs(d) < 1 || abs(d) > 3 || check != isDescending)
            return false;
    }

    return true;
}

bool isSafePart2(vector<int> &nums)
{

    if (isSafePart1(nums))
        return true;
    else
        for (int i = 0; i < nums.size(); i++)
        {
            vector<int> tmp = nums;
            tmp.erase(tmp.begin() + i);
            if (isSafePart1(tmp))
                return true;
        }
    return false;
}