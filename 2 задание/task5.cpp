#include <iostream>
using namespace std;

int func(int a, int &b) {
    if (a / 10 != 0) {
        int c = func(a / 10, b);
        b *= 10;
        return (a % 10) * b + c;

    }
    else {
        return a;
    }
}

int main()
{
    int a;
    int b = 1;
    cin >> a;
    cout << func(a, b);
    return 0;
}
