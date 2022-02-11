#include <iostream>
using namespace std;

int b = 1;

int func(int N)
{
    cout << "Enter an integer: ";
    int current = 0;
    cin >> current;
    int minelem = current;
    --N;
    for (int i = 0; i < N; i++)
    {
        cout << "Enter an integer: ";
        cin >> current;
        if (current == minelem)
        {
            b++;
        }
        if (current < minelem)
        {
            minelem = current;
            b = 1;
        }
    }
    return minelem;
}

int main()
{
    int MinElem, n;
    cout << "Enter number of elements ";
    cin >> n;
    MinElem = func(n);
    cout << "The minimal element: " << MinElem << endl;
    cout << "The number of repetition: " << b;
}
