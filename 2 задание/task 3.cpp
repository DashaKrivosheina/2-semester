#include <iostream>
using namespace std;

void func(int& a, int& b) {
    int c;
    cin >> c;
    if (c != 0) {
        a += c;
        b++;
        func(a, b);
    }
}

int main()
{
    int a = 0;
    int b = 0;
    func(a, b);
    cout << a / b;
}
