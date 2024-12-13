#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

ll part1();
ll part2();

int main()
{
    cout << "Part 1: " << part1() << endl;
    cout << "Part 2: " << part2() << endl;
}

ll process(pair<ll, ll> A, pair<ll, ll> B, pair<ll, ll> target)
{
    ll A1 = A.first, B1 = B.first, C1 = target.first;
    ll A2 = A.second, B2 = B.second, C2 = target.second;

    ll D = A1 * B2 - A2 * B1;
    ll Dx = C1 * B2 - C2 * B1;
    ll Dy = A1 * C2 - A2 * C1;

    if (D == 0)
        return 0;

    if (Dx % D != 0 || Dy % D != 0)
        return 0;

    ll x = Dx / D;
    ll y = Dy / D;

    if (x < 0 || y < 0)
        return 0;

    return 3 * x + y;
}

ll part1()
{
    ifstream input("input.txt");
    string line;
    ll res = 0;

    while (getline(input, line))
    {
        pair<ll, ll> A, B, target;

        sscanf(line.c_str(), "Button A: X+%d, Y+%d", &A.first, &A.second);
        getline(input, line);
        sscanf(line.c_str(), "Button B: X+%d, Y+%d", &B.first, &B.second);
        getline(input, line);
        sscanf(line.c_str(), "Prize: X=%d, Y=%d", &target.first, &target.second);
        getline(input, line);

        res += process(A, B, target);
    }

    return res;
}

ll part2()
{
    ifstream input("input.txt");
    string line;
    ull res = 0;

    while (getline(input, line))
    {
        pair<ll, ll> A, B, target;

        sscanf(line.c_str(), "Button A: X+%d, Y+%d", &A.first, &A.second);
        getline(input, line);
        sscanf(line.c_str(), "Button B: X+%d, Y+%d", &B.first, &B.second);
        getline(input, line);
        sscanf(line.c_str(), "Prize: X=%d, Y=%d", &target.first, &target.second);
        getline(input, line);

        target.first += ull(1e13);
        target.second += ull(1e13);

        res += process(A, B, target);
    }

    return res;
}