#include <iostream>
using namespace std;

void func() {
    int a;
    cin >> a;
    if (a != 0) {
        int b;
        cin >> b;
        cout << a << " ";
        if (b != 0) {
            func();
        }
    } 
}

int main()
{
    func();
}
