#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

//генерация рандомных чисел
float random(int k) {
    float f = (rand() % k);
    return f;
}

void func() {
    srand(static_cast<unsigned int>(time(0)));;
    for (unsigned int m = 0; m < 501; ++m) {
        for (int k = 0; k < 400; ++k) {
            ofstream outf("task11.txt", ios::app);
            const int n = 500;
            int A[n][n];
            for (unsigned int i = 0; i < m; ++i) {
                for (unsigned int j = 0; j < m; ++j) {
                    A[i][j] = 1;
                }
            }
            int x = m / 2;
            int y = m / 2;   
            A[x][y] = 0;
            bool end = 0;
            for (int step = 0; !end; ++step) {
                if (x == 0 || x == m - 1 || y == 0 || y == m - 1) {
                    outf << m << " " << step << "\n";
                    end = 1;
                }
                else {
                    int v = random(4);
                    if (v == 0) {
                        x++;
                    }
                    if (v == 1) {
                        x--;
                    }
                    if (v == 2) {
                        y++;
                    }
                    if (v == 3) {
                        y--;
                    }
                }
            }
        }
    }
}

int main()
{
    func();
}
