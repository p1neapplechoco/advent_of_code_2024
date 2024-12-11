#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

int part1();
int part2();

int main()
{
    cout << "Part 1: " << part1() << endl;
    cout << "Part 2: " << part2() << endl;
}

long long processPart1(string content)
{
    if (content.empty())
        return 0;

    if (content.find("mul(") == string::npos)
        return 0;

    int pos = content.find("mul(") + 4;

    if (pos > content.size())
        return 0;

    string tmp = "";

    while (pos < content.size() && content[pos] != ',')
    {
        if (content[pos] < '0' || content[pos] > '9')
            return 0 + processPart1(content.substr(pos));
        tmp += content[pos];
        pos++;
    }
    int a = stoi(tmp);
    pos++;

    tmp.clear();

    while (pos < content.size() && content[pos] != ')')
    {
        if (content[pos] < '0' || content[pos] > '9')
            return 0 + processPart1(content.substr(pos));
        tmp += content[pos];
        pos++;
    }
    int b = stoi(tmp);

    return a * b + processPart1(content.substr(pos));
}

long long processPart2(string content)
{
    if (content.empty())
        return 0;
    if (content.find("don't()") == string::npos)
        return processPart1(content);

    if (content.find("do()") == string::npos)
        return processPart1(content.substr(0, content.find("don't()") + 7));

    int do_pos = content.find("do()");
    int dont_pos = content.find("don't()");

    if (do_pos < dont_pos)
        return processPart1(content.substr(0, do_pos)) + processPart2(content.substr(do_pos + 4));
    else
        return processPart1(content.substr(0, dont_pos)) + processPart2(content.substr(do_pos + 4));
}

int part1()
{
    ifstream input("input.txt");
    ostringstream oss;

    oss << input.rdbuf();
    string content = oss.str();

    input.close();

    return processPart1(content);
}

int part2()
{
    ifstream input("input.txt");
    ostringstream oss;

    oss << input.rdbuf();
    string content = oss.str();

    input.close();

    return processPart2(content);
}