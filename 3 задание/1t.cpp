#include <iostream>
using namespace std;

int func(int n) {
    int* a = new int[n];
    int* s = new int(0);
    int* p = new int(0);
    int* curr = new int(2147483647);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        if (a[i] < 0) {
            (*s)++;
            for (int j = i + 1; j < n; j++) {
                if (a[i] + a[j] == 0) {
                    (*p)++;
                    if ((*curr) > j - i) {
                        *curr = j - i;
                    }
                    break;
                }
                
            }
            
        }
    }
    if (*s == 0 || *s == n || *p == 0) {
        cout << 0;
        return 0;
    }
    cout << *curr;
    delete[] a;
    delete s;
    delete p;
    delete curr;
    return 0;
}

int main()
{
    int n;
    cin >> n;
    if (n == 0) {
        cout << 0;
        return 0;
    }
    func(n);
}
