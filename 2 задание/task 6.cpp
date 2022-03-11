#include <iostream>
using namespace std;
int mfunc(int n);

int ffunc(int n) {
    if (n == 0) {
        return 1;
    }
    else {
        return n - mfunc(ffunc(n - 1));
    }
}

int mfunc(int n) {
    if (n == 0) {
        return 0;
    }
    else {
        return n - ffunc(mfunc(n - 1));
    }
}

int main()
{
    int n;
    cin >> n;
    cout << ffunc(n) << " " << mfunc(n);
}