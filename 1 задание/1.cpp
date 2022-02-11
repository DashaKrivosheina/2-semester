#include <iostream>
using namespace std;

int func(int N)
{
    cout << "Enter an integer: ";
    int current = 0;
    cin >> current;
    int maxelem = current;
    --N;
    for (int i = 0; i < N; i++)
    {
        cout << "Enter an integer: ";
        cin >> current;
        if (current > maxelem && current % 2 == 0)
        {
            maxelem = current;
        }
    }
    return maxelem;
}

int main()
{
    int MaxElem, n;
    cout << "Enter number of elements";
    cin >> n;
    MaxElem = func(n);
    if (MaxElem % 2 == 0)
    {
        cout << "The biggest even element: " << MaxElem;
    }
    else
    {
        cout << "The biggest even element: 0";
    }
}
