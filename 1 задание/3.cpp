#include <iostream>
using namespace std;

int func(int N)
{
    cout << "Enter an height: ";
    int current = 0;
    cin >> current;
    int height = current;
    --N;
    int pair = 0;
    for (int i = 0; i < N; i++)
    {
        cout << "Enter an height: ";
        cin >> current;
        if (current > height)
        {
            pair++;
        }
    }
    return pair;
}

int main()
{
    int Pair, n;
    cout << "Enter number of students ";
    cin >> n;
    Pair = func(n);
    cout << "The number od wrong pair: " << Pair;
}
