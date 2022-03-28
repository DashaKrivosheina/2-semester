#include <iostream>
using namespace std;

using std::cin;
using std::cout;
using std::endl;

void my_personal_swap(int* c, int* d) {
	if (c == nullptr || d == nullptr) {
		return;
	}
	int x;
	x = *d;
	*d = *c;
	*c = x;
}

int main() {
	int a, b;
	cin >> a >> b;
	my_personal_swap(&a, &b);
	cout << a << " " << b << endl;
	my_personal_swap(&a, nullptr);
	my_personal_swap(nullptr, &b);
	my_personal_swap(nullptr, nullptr);
	return 0;
}