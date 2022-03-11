#include <iostream>
using namespace std;

void func(int &a, int &n) {
    int c;
    cin >> c;
    if (c != 0) {
        if (c > a) {
            a = c;
            n = 1;
        }
        else if (c == a) {
            n++;
        }
        func(a, n);
    }
}

int main()
{
    int a = 0;
    int n = 0;
    func(a, n);
    cout << n;
}