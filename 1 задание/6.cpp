#include <iostream>
using namespace std;

void func(float x, float y, float a, float b, float r)
{
    if ((x - a) * (x - a) + (y - b) * (y - b) <= r * r)
    {
        cout << "YES";
    }
    else
    {
        cout << "No";
    }
}

int main()
{
    float x, y, a, b, r;
    cout << "Enter point coordinates: ";
    cin >> x >> y;
    cout << "Enter circle coordinates and radius: ";
    cin >> a >> b >> r;
    func(x, y, a, b, r);
}

