#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

void readFilePart1(string, vector<int> &, vector<int> &);
void readFilePart2(string, vector<int> &, map<int, int> &);
void countingSort(vector<int> &);

int part1();
int part2();

int main()
{
    cout << "Part 1: " << part1() << endl;
    cout << "Part 2: " << part2() << endl;
}

int part1()
{
    vector<int> arr_1;
    vector<int> arr_2;

    readFilePart1("input.txt", arr_1, arr_2);

    countingSort(arr_1);
    countingSort(arr_2);

    int res = 0;
    int n = arr_1.size();
    for (int i = 0; i < n; i++)
        res += abs(arr_1[n - i - 1] - arr_2[n - i - 1]);
    return res;
}

int part2()
{
    vector<int> arr;
    map<int, int> mp;

    readFilePart2("input.txt", arr, mp);

    int res = 0;
    for (int e : arr)
        res += e * mp[e];

    return res;
}

void readFilePart1(string filename, vector<int> &arr_1, vector<int> &arr_2)
{
    ifstream input(filename);
    string line;

    while (getline(input, line))
    {
        int idx = line.find_first_of(' ');
        arr_1.push_back(stoi(line.substr(0, idx + 1)));
        arr_2.push_back(stoi(line.substr(idx + 1)));
    }

    input.close();
}

void readFilePart2(string filename, vector<int> &arr, map<int, int> &mp)
{
    ifstream input(filename);
    string line;

    while (getline(input, line))
    {
        int idx = line.find_first_of(' ');
        arr.push_back(stoi(line.substr(0, idx + 1)));
        mp[stoi(line.substr(idx + 1))]++;
    }

    input.close();
}

void countingSort(vector<int> &arr)
{
    int n = arr.size();
    int max_ele = arr[0];
    for (int i = 0; i < n; i++)
        if (arr[i] > max_ele)
            max_ele = arr[i];

    int *count_arr = new int[max_ele + 1]{};

    for (int i = 0; i < n; i++)
        count_arr[arr[i]]++;

    for (int i = 1; i < max_ele + 1; i++)
        count_arr[i] += count_arr[i - 1];

    int *new_arr = new int[n]; // for output

    for (int i = n - 1; i >= 0; i--)
        new_arr[count_arr[arr[i]]-- - 1] = arr[i];

    for (int i = 0; i < n; i++)
        arr[i] = new_arr[i];

    delete new_arr;
}