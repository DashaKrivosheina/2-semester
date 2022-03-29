#include <iostream>
using namespace std;

void func(double& a, double& b) {
    double c;
    cin >> c;
    if (c != 0) {
        a += c;
        b++;
        func(a, b);
    }
}

double main()
{
    double a = 0;
    double b = 0;
    func(a, b);
    cout << a / b;
}
