#include <iostream>
using namespace std;

void func() {
    int a;
    cin >> a;
    if (a % 2 == 1) {
        cout << a << " ";
    }
    if (a != 0) {
        func();
    }
}

int main()
{
    func();
}
