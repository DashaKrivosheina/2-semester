#include <iostream>
using namespace std;

void func(int n) {
	int* a = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	if (n % 2 == 1) {
		for (int j = n - 1; j >= 0; j = j - 2) {
			cout << a[j] << " ";
		}
		for (int k = n - 2; k >= 0; k = k - 2) {
			cout << a[k] << " ";
		}
	}
	else {
		for (int k = n - 2; k >= 0; k = k - 2) {
			cout << a[k] << " ";
		}
		for (int j = n - 1; j >= 0; j = j - 2) {
			cout << a[j] << " ";
		}
	}
	delete[] a;
}

int main() {
	int n;
	cin >> n;
	func(n);
}